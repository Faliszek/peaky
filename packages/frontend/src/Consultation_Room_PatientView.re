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
    if(data !== "") {
      canvas.loadPaths(data);
    }
  }
|}
];

let clearCanvas = [%bs.raw
  {|
  function(canvas) {
    if(canvas) {
      canvas.clearCanvas();
      }
  }
|}
];

let useSharedData =
    (~peer, ~userIds, ~myId, ~setPatientId, ~patientId, ~setData) => {
  open Peer;

  let incoming = React.useRef(None);

  let calls: React.ref(array(option(Connection.t))) = React.useRef([||]);

  let send = (conn, value) => conn->Connection.send(value)->ignore;

  let onDataChange =
    React.useCallback1(
      data => {
        switch (incoming.current) {
        | Some(i) => i->send(data)->ignore
        | None => ()
        };
        calls.current
        ->Array.map(c =>
            switch (c) {
            | Some(c) => c->send(data)
            | None => ()
            }
          )
        ->ignore;
      },
      [|patientId|],
    );

  React.useEffect0(() => {
    let handleConnection = c => {
      switch (c) {
      | Some(c) =>
        c
        ->Connection.onOpen("open", _ => {
            c->Connection.onData("data", data => {
              setPatientId(v => v == data.patientId ? v : data.patientId);
              if (data.updater != myId) {
                setData(_ => data.canvas);
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

    calls.current =
      userIds->Array.map(x =>
        Obj.magic(peer->connect(x, {serialization: "json"}))
      );
    calls.current->Array.map(x => {handleConnection(x)})->ignore;

    None;
  });

  onDataChange;
};

let initalData = (myId, userIds) => {
  userIds
  ->Array.concat([|myId|])
  ->Array.map(u => {Peer.Connection.id: u, svg: ""});
};

[@react.component]
let make = (~callerId, ~myId, ~userIds: array(string), ~peer) => {
  let query = Query.use();
  let patient = Select.use();
  let callerId = "data" ++ callerId;
  let (color, setColor) = React.useState(_ => "rgb(96, 165, 250)");
  let (visible, setVisible) = React.useState(_ => false);
  let (patientId, setPatientId) = React.useState(_ => None);

  let (data, setData) = React.useState(_ => initalData(myId, userIds));

  let canvasEl = React.useRef(None);

  let onDataChange =
    useSharedData(
      ~peer,
      ~userIds,
      ~patientId,
      ~setPatientId,
      ~myId,
      ~setData,
    );

  React.useEffect1(
    () => {
      onDataChange({
        patientId,
        canvas: initalData(myId, userIds),
        updater: myId,
      });
      clearCanvas(canvasEl.current)->ignore;
      None;
    },
    [|patientId|],
  );

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
           saveElCanvas={el => {canvasEl.current = Some(el)}}
         />
       </div>
     | _ => React.null
     }}
  </div>;
};
