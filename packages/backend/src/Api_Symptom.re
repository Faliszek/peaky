type addSymptomPayload = {
  patientId: string,
  symptompId: string,
  feeling: string,
  timestamp: string,
};

let add = (payload: addSymptomPayload, context: Graphql_Context.t) => {
  let createdRecordId =
    context.db
    ->Firebase.Database.ref(~path="/symptoms", ())
    ->Firebase.Database.Reference.push(~value=payload, ())
    ->Firebase.Database.Reference.key
    ->Js.Nullable.toOption;

  switch (createdRecordId) {
  | Some(id) =>
    let r = context.db->Firebase.Database.ref(~path="/symptoms/" ++ id, ());
    r
    ->Firebase.Database.Reference.once(~eventType="value", ())
    ->Promise.Js.toResult
    ->Promise.Js.map(res => {
        switch (res) {
        | Ok(res) => res->Json.toObject(id)
        | Error(err) => Json.fromObject(err)
        }
      });

  | None => Promise.resolved(None)
  };
};

type listPayload = {patientId: string};

let list = (payload: listPayload, context: Graphql_Context.t) => {
  context.db
  ->Chain.get("/symptoms")
  ->Chain.onFinish(~onOk=feelings => {
      feelings->Json.toOwnedList(payload.patientId, `patient)
    });
};
