type createPayload = {
  patientId: string,
  doctorId: string,
};

let add = (payload: createPayload, context: Graphql_Context.t) => {
  let createdRecordId =
    context.db
    ->Firebase.Database.ref(~path="/rooms", ())
    ->Firebase.Database.Reference.push(~value=payload, ())
    ->Firebase.Database.Reference.key
    ->Js.Nullable.toOption;

  switch (createdRecordId) {
  | Some(id) =>
    let r = context.db->Firebase.Database.ref(~path="/rooms/" ++ id, ());
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

type getPayload = {id: string};

let get = (payload: getPayload, context: Graphql_Context.t) => {
  let r =
    context.db->Firebase.Database.ref(~path="/rooms/" ++ payload.id, ());
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

let stopMeeting = () => {};
