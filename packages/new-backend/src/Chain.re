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
