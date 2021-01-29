[@decco]
type createVisitPayload = {
  patientId: string,
  from_: string,
  to_: string,
  notes: string,
};

type connectedPayload = {
  patientId: string,
  from_: string,
  to_: string,
  notes: string,
  doctorId: string,
};

type removeVisitResponse = {id: string};

let toRecord = (payload: createVisitPayload, ~id: string): Domain.Visit.t => {
  let {patientId, from_, to_, notes} = payload;
  {patientId, from_, to_, notes, id};
};

let createVisit = (payload: createVisitPayload, context: Graphql_Context.t) => {
  let {user_id} = Auth.decode(context.token);
  let createdRecordId =
    context.db
    ->Firebase.Database.ref(~path="/visits", ())
    ->Firebase.Database.Reference.push(
        ~value={
          patientId: payload.patientId,
          from_: payload.from_,
          to_: payload.to_,
          notes: payload.notes,
          doctorId: user_id,
        },
        (),
      )
    ->Firebase.Database.Reference.key
    ->Js.Nullable.toOption;

  switch (createdRecordId) {
  | Some(id) =>
    let r = context.db->Firebase.Database.ref(~path="/visits/" ++ id, ());
    r
    ->Firebase.Database.Reference.once(~eventType="value", ())
    ->Promise.Js.toResult
    ->Promise.Js.map(res => {
        switch (res) {
        | Ok(res) =>
          switch (
            Firebase.Database.DataSnapshot.val_(res)
            ->createVisitPayload_decode
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

let remove = (payload: removeVisitResponse, context: Graphql_Context.t) => {
  context.db
  ->Firebase.Database.ref(~path="/visits/" ++ payload.id, ())
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
  let r = context.db->Firebase.Database.ref(~path="/visits", ());
  r
  ->Firebase.Database.Reference.once(~eventType="value", ())
  ->Promise.Js.toResult
  ->Promise.Js.map(res => {
      switch (res) {
      | Ok(res) =>
        let {user_id} = Auth.decode(context.token);
        res->Json.toList(user_id);

      | Error(err) => Json.fromObject(err)
      }
    });
};
