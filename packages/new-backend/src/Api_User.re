type meQueryPayload;

[@decco]
type userData = {
  email: string,
  specialization: string,
  firstName: string,
  lastName: string,
  patients: option(array(Domain.Patient.t)),
};

[@decco]
type userList = array(userData);

let toRecord = (~id: string, payload: userData): Domain.User.t => {
  let {firstName, lastName, specialization, email, patients} = payload;
  {id, firstName, lastName, specialization, email, patients};
};

let me = (_payload: meQueryPayload, context: Graphql_Context.t) => {
  let {user_id} = Auth.decode(context.token);

  Firebase.(
    context.db
    ->Database.ref(~path="/users/" ++ user_id, ())
    ->Database.Reference.once(~eventType="value", ())
    ->Promise.Js.toResult
    ->Promise.Js.map(res => {
        switch (res) {
        | Ok(res) =>
          switch (Database.DataSnapshot.val_(res)->userData_decode) {
          | Ok(res) => res->toRecord(~id=user_id)
          | Error(err) =>
            Js.log(err);
            Json.fromObject(err);
          }
        | Error(err) => Json.fromObject(err)
        }
      })
  );
};
type searchPayload = {
  specialization: string,
  firstName: string,
  lastName: string,
};
let search = (payload: searchPayload, context: Graphql_Context.t) => {
  let {user_id} = Auth.decode(context.token);

  Firebase.(
    context.db
    ->Database.ref(~path="/users", ())
    ->Database.Reference.once(~eventType="value", ())
    ->Promise.Js.toResult
    ->Promise.Js.map(res => {
        switch (res) {
        | Ok(res) =>
          let {specialization, firstName, lastName} = payload;
          let data: array(Domain.User.t) = res->Json.toList;

          data->Array.keep(u =>
            switch (specialization, firstName, lastName, user_id) {
            | (_, _, _, userId) when userId == u.id => false
            | ("", "", "", _) => true
            | (specialization, _, _, _)
                when u.specialization->Js.String2.includes(specialization) =>
              true
            | (_, firstName, _, _)
                when u.firstName->Js.String2.includes(firstName) =>
              true
            | (_, _, lastName, _)
                when u.lastName->Js.String2.includes(lastName) =>
              true
            | _ => false
            }
          );

        | Error(err) => Json.fromObject(err)
        }
      })
  );
};
