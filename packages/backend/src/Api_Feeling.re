type addFeelingPayload = {
  patientId: string,
  value: string,
  timestamp: string,
};

let add = (payload: addFeelingPayload, context: Graphql_Context.t) => {
  let createdRecordId =
    context.db
    ->Firebase.Database.ref(~path="/feelings", ())
    ->Firebase.Database.Reference.push(~value=payload, ())
    ->Firebase.Database.Reference.key
    ->Js.Nullable.toOption;

  switch (createdRecordId) {
  | Some(id) =>
    let r = context.db->Firebase.Database.ref(~path="/feelings/" ++ id, ());
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
  ->Chain.get("/feelings")
  ->Chain.onFinish(~onOk=feelings => {
      feelings->Json.toOwnedList(payload.patientId, `patient)
    });
};
