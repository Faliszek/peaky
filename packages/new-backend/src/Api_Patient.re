[@decco]
type createPatientPayload = {
  firstName: string,
  lastName: string,
  phoneNumber: string,
  disease: string,
  color: string,
};

type connectedPayload = {
  firstName: string,
  lastName: string,
  phoneNumber: string,
  disease: string,
  doctorId: string,
  color: string,
};

type removePatientResponse = {id: string};

let toRecord = (payload: createPatientPayload, ~id: string): Domain.Patient.t => {
  let {firstName, lastName, phoneNumber, disease, color} = payload;
  {id, firstName, lastName, phoneNumber, disease, treatment: [], color};
};

let createPatient =
    (payload: createPatientPayload, context: Graphql_Context.t) => {
  let {user_id} = Auth.decode(context.token);

  let createdRecordId =
    context.db
    ->Firebase.Database.ref(~path="/patients", ())
    ->Firebase.Database.Reference.push(
        ~value={
          firstName: payload.firstName,
          lastName: payload.lastName,
          phoneNumber: payload.phoneNumber,
          disease: payload.disease,
          doctorId: user_id,
          color: payload.color,
        },
        (),
      )
    ->Firebase.Database.Reference.key
    ->Js.Nullable.toOption;

  switch (createdRecordId) {
  | Some(id) =>
    let r = context.db->Firebase.Database.ref(~path="/patients/" ++ id, ());
    r
    ->Firebase.Database.Reference.once(~eventType="value", ())
    ->Promise.Js.toResult
    ->Promise.Js.map(res => {
        switch (res) {
        | Ok(res) =>
          switch (
            Firebase.Database.DataSnapshot.val_(res)
            ->createPatientPayload_decode
          ) {
          | Ok(res) => Some(res->toRecord(~id))
          | Error(err) => Json.fromObject(err)
          }
        | Error(err) => Json.fromObject(err)
        }
      });

  | None => Promise.resolved(None)
  };
};

let removePatient =
    (payload: removePatientResponse, context: Graphql_Context.t) => {
  context.db
  ->Firebase.Database.ref(~path="/patients/" ++ payload.id, ())
  ->Firebase.Database.Reference.set(~value=Js.Nullable.null, ())
  ->Promise.Js.toResult
  ->Promise.Js.map(res => {
      switch (res) {
      | Ok(_) => Some({id: payload.id})
      | Error(_) => None
      }
    });
};

type listPayload;

let list = (_payload: listPayload, context: Graphql_Context.t) => {
  let r = context.db->Firebase.Database.ref(~path="/patients", ());
  r
  ->Firebase.Database.Reference.once(~eventType="value", ())
  ->Promise.Js.toResult
  ->Promise.Js.map(res => {
      Js.log(res);
      switch (res) {
      | Ok(res) =>
        let {user_id} = Auth.decode(context.token);
        res->Json.toList(user_id);

      | Error(err) => Json.fromObject(err)
      };
    });
};

type singlePayload = {id: string};
let single = (payload: singlePayload, context: Graphql_Context.t) => {
  let r =
    context.db->Firebase.Database.ref(~path="/patients/" ++ payload.id, ());
  r
  ->Firebase.Database.Reference.once(~eventType="value", ())
  ->Promise.Js.toResult
  ->Promise.Js.map(res => {
      switch (res) {
      | Ok(res) => res->Json.toObject(payload.id)
      | Error(err) => Json.fromObject(err)
      }
    });
};
