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

let get = (db, path) => {
  Firebase.(
    db
    ->Database.ref(~path, ())
    ->Database.Reference.once(~eventType="value", ())
    ->Promise.Js.toResult
  );
};

let onFinish = (req, ~onOk) =>
  req->Promise.Js.map(res => {
    switch (res) {
    | Ok(res) => onOk(res)
    | Error(err) => Json.fromObject(err)
    }
  });

type listPayload;

let list = (_payload: listPayload, context: Graphql_Context.t) => {
  //   context.db
  //   ->get("/users")
  //   ->onFinish(~onOk=res => {
  //       let users = res->Json.toUserList;
  //       context.db
  //       ->get("/calls")
  //       ->onFinish(~onOk=calls => {calls->Json.toCallsList(users)});
  //     });
  context.db
  ->get("/users")
  ->onFinish(~onOk=Json.toUserList)
  ->Promise.flatMap(users =>
      context.db
      ->get("/calls")
      ->onFinish(~onOk=calls => {calls->Json.toCallsList(users)})
    );
};
