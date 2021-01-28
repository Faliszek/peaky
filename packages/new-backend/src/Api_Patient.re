[@decco]
type createPatientPayload = {
  firstName: string,
  lastName: string,
  phoneNumber: string,
  disease: string,
};

type removePatientResponse = {id: string};

let toRecord = (payload: createPatientPayload, ~id: string): Domain.Patient.t => {
  let {firstName, lastName, phoneNumber, disease} = payload;
  {id, firstName, lastName, phoneNumber, disease, treatment: []};
};

let createPatient =
    (payload: createPatientPayload, context: Graphql_Context.t) => {
  let createdRecordId =
    context.db
    ->Firebase.Database.ref(~path="/patients", ())
    ->Firebase.Database.Reference.push(~value=payload, ())
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
