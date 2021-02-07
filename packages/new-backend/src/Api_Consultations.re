type listPayload;

let list = (_payload: listPayload, context: Graphql_Context.t) => {
  context.db->Chain.get("/consultations")->Chain.onFinish(~onOk=Json.toList);
};

type createPayload;

let create = (payload: createPayload, context: Graphql_Context.t) => {
  let createdRecordId =
    context.db
    ->Firebase.Database.ref(~path="/consultations", ())
    ->Firebase.Database.Reference.push(~value=payload, ())
    ->Firebase.Database.Reference.key
    ->Js.Nullable.toOption;

  switch (createdRecordId) {
  | Some(id) =>
    let r =
      context.db->Firebase.Database.ref(~path="/consultations/" ++ id, ());
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

type declinePayload = {
  id: string,
  callerId: string,
  userIds: array(string),
};

type payloadToReturn = {
  callerId: string,
  userIds: array(string),
};

let decline = (payload: declinePayload, context: Graphql_Context.t) => {
  Js.log(payload);
  context.db
  ->Firebase.Database.ref(~path="/consultations/" ++ payload.id, ())
  ->Firebase.Database.Reference.set(
      ~value={callerId: payload.callerId, userIds: payload.userIds},
      (),
    )
  ->Promise.Js.toResult
  ->Promise.Js.map(res => {
      Domain.Consultation.(
        switch (res) {
        | Ok(_) =>
          Some({
            id: payload.id,
            callerId: payload.callerId,
            userIds: payload.userIds,
          })
        | Error(_) => None
        }
      )
    });
};
