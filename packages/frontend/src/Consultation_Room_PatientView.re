open Patient_List_Query;
let toSelectOptions = patients => {
  Query.(
    Select.(
      patients->Array.map(p =>
        {value: p.id, label: p.firstName ++ " " ++ p.lastName}
      )
    )
  );
};

let updateCanvas = [%bs.raw
  {|
  function(canvas, data) {
    console.log("I DO WHATEVER THE FUCK I WANT", canvas, data);
    if(data !== "") {
      canvas.loadPaths(data);
    }
  }
|}
];

let useSharedData =
    (
      ~peer,
      ~userIds,
      ~callerId,
      ~myId,
      ~canvas: React.Ref.t(array('b)),
      ~setPatientId,
      ~patientId,
      ~canvasEl: React.Ref.t('a),
      ~setData,
    ) => {
  open Peer;

  let userIds =
    userIds
    ->Array.concat([|callerId|])
    ->Array.keep(u => u != myId)
    ->Array.map(u => "data" ++ u);

  let myConn = React.useRef(None);
  let incoming = React.useRef(None);

  let calls = React.useRef([||]);

  let send = (conn, value) => conn->Connection.send(value)->ignore;

  let onDataChange =
    React.useCallback1(
      data => {
        switch (incoming.current) {
        | Some(i) => i->send(data)->ignore
        | None => ()
        };
        // nDataChange({patientId, canvas: data, updater: myId})
        calls.current->Array.map(c => c->send(data))->ignore;
      },
      [|patientId|],
    );

  React.useEffect0(() => {
    Js.log("ONLY ONCE");
    let handleConnection = c => {
      switch (c) {
      | Some(c) =>
        c
        ->Connection.onOpen("open", _ => {
            // Will print 'this is a test'
            c->Connection.onData("data", data => {
              setPatientId(v => v == data.patientId ? v : data.patientId);
              Js.log3("updater", data.updater, myId);
              if (data.updater != myId) {
                setData(_ => data.canvas);
                Js.log2(
                  "DATA",
                  data.canvas,
                  // switch (canvasEl.current) {
                  // | Some(el) => updateCanvas(el, data.canvas)
                  // | _ => ()
                  // };
                  // canvas.current = data.canvas;
                  // Js.log2(
                  //   "EL",
                  //   canvasEl,
                  //   // setResetKey(x => x + 1);
                  // );
                );
              };
            })
          })
        ->ignore
      | None => ()
      };
    };

    peer->onConnection("connection", conn => {
      incoming.current = Some(conn);
      handleConnection(incoming.current);
    });

    // myConn.current = Some(peer->connect(userId));
    // handleConnection(myConn.current);

    calls.current =
      userIds->Array.map(x => peer->connect(x, {serialization: "json"}));
    calls.current
    ->Array.map(x => {
        Js.log2("connection", x);
        handleConnection(Some(x));
      })
    ->ignore;

    None;
  });

  onDataChange;
};

[@react.component]
let make = (~callerId, ~myId, ~userIds: array(string), ~peer) => {
  open Peer;

  let query = Query.use();
  let patient = Select.use();

  let (color, setColor) = React.useState(_ => "rgb(96, 165, 250)");

  let (visible, setVisible) = React.useState(_ => false);

  // let (resetKey, setResetKey) = React.useState(_ => 0);
  // let (time, setTime) = React.useState(_ => 0);

  //   let userIds = userIds->Array.map(u => "data" ++ u);

  //   let userIds =
  // userIds->Array.concat([|callerId|])->Array.keep(u => u != myId);

  // let myId = "data" ++ myId;
  // Js.log(userIds);
  let (patientId, setPatientId) = React.useState(_ => None);
  let canvas = React.useRef([||]);
  let canvasEl = React.useRef(None);

  let (data, setData) =
    React.useState(_ =>
      [|callerId|]
      ->Array.concat(userIds)
      ->Array.map(u => Connection.{id: u, svg: ""})
    );
  // let lock = React.useRef(0);

  // Js.log2("LOCK", lock.current);

  let onDataChange =
    useSharedData(
      ~peer,
      ~canvas,
      ~patientId,
      ~setPatientId,
      ~userIds,
      ~callerId,
      ~myId,
      ~canvasEl,
      ~setData,
    );

  React.useEffect1(
    () => {
      Js.log(data);
      onDataChange({patientId, canvas: data, updater: myId});
      None;
    },
    [|patientId|],
  );

  // React.useEffect0(() => {
  //   let interval = Timeout.setInterval(() => {setTime(x => x + 1)}, 200);

  //   Some(() => Timeout.clearInterval(interval));
  // });

  <div className="w-full h-screen flex items-center">
    {switch (query) {
     | {loading: true} => <Spinner />
     | {data: Some({patients})} =>
       <div className="h-full py-8 px-4 w-full">
         <div
           className="w-full flex gap-8 justify-between shadow-lg sticky border-bottom border-gray-300 top-0 p-4 rounded-xl z-20 bg-white">
           {callerId == myId
              ? <div className="flex gap-8 justify-between">
                  <Select
                    value={patient.value}
                    search={patient.search}
                    visible={patient.visible}
                    onChange={patient.setValue}
                    onSearchChange={patient.setSearch}
                    onVisibleChange={patient.setVisible}
                    placeholder={j|Wybierz pacjenta|j}
                    icon={<Icons.User size="20" />}
                    options={patients->toSelectOptions}
                  />
                  <Button.CTA
                    onClick={_ =>
                      setPatientId(_ =>
                        patient.value->Option.map(x => x.value)
                      )
                    }>
                    <Text> {j|Wybierz|j} </Text>
                  </Button.CTA>
                </div>
              : React.null}
           <div className="flex items-center">
             {[||]->Array.size != 0
                ? <Button.CTA icon={<Icons.ArrowLeft className="mr-2" />}>
                    <Text> {j|Cofnij|j} </Text>
                  </Button.CTA>
                : React.null}
             <Button.Nav
               onClick={_ => setVisible(v => !v)} className="relative">
               <span style={ReactDOM.Style.make(~color, ())}>
                 <Icons.Edit3 />
               </span>
               {visible
                  ? <Color_Picker
                      value=color
                      onChange={v => setColor(_ => v)}
                      className="w-48 absolute right-0 top-4 border border-gray-200 shadow-lg bg-white p-4 z-30"
                    />
                  : React.null}
             </Button.Nav>
           </div>
         </div>
         <Consultation_Room_PatientData
           userIds
           patientId
           color
           myId
           callerId
           data
           onChange={(svg: string) => {
             onDataChange({
               patientId,
               canvas: data->Array.map(x => x.id == myId ? {...x, svg} : x),
               updater: myId,
             })
           }}
           //  ;
           saveElCanvas={el => {canvasEl.current = Some(el)}}
           //  data={canvas.current}
         />
       </div>
     | _ => React.null
     }}
  </div>;
};
