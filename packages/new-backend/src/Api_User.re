type meQueryPayload;

type payload = {user_id: string};

[@module "jwt-decode"] external decode: option(string) => payload = "default";

[@decco]
type userData = {
  email: string,
  specialization: string,
  firstName: string,
  lastName: string,
  patients: option(array(Domain.Patient.t)),
};

let toRecord = (~id: string, payload: userData): Domain.User.t => {
  let {firstName, lastName, specialization, email, patients} = payload;
  {id, firstName, lastName, specialization, email, patients};
};

let me = (_payload: meQueryPayload, context: Graphql_Context.t) => {
  let {user_id} = decode(context.token);
  Js.log3("USER", user_id, context.token);
  Firebase.(
    Domain.(
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
    )
  );
};
