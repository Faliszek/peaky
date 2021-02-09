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

[@react.component]
let make = (~callerId, ~myId, ~userIds, ~peer) => {
  let query = Query.use();
  let patient = Select.use();

  let (color, setColor) = React.useState(_ => "rgb(96, 165, 250)");

  let (visible, setVisible) = React.useState(_ => false);

  //   let userIds = userIds->Array.map(u => "data" ++ u);

  //   let userIds =
  // userIds->Array.concat([|callerId|])->Array.keep(u => u != myId);

  // let myId = "data" ++ myId;
  // Js.log(userIds);
  let userIds =
    userIds
    ->Array.concat([|callerId|])
    ->Array.keep(u => u != myId)
    ->Array.map(u => "data" ++ u);

  Js.log3("IDS", myId, userIds);
  let myConn = React.useRef(None);
  // let incoming = React.useRef(None);
  let incoming = React.useRef(None);

  let calls = React.useRef([||]);
  //   let (value, setValue) = React.useState(_ => "dupa");

  let (patientId, setPatientId) = React.useState(_ => None);
  let (canvas, setCanvas) = React.useState(_ => None);

  React.useEffect0(() => {
    open Peer;

    let handleConnection = c => {
      switch (c) {
      | Some(c) =>
        c
        ->Connection.onOpen("open", _ => {
            // Will print 'this is a test'
            c->Connection.onData("data", data => {
              setPatientId(v => v == data.patientId ? v : data.patientId);
              if (data.canvas != canvas) {
                setCanvas(_ => data.canvas);
              };

              Js.log2(
                "ON RECEIVE",
                data,
                //   if (data != patientId) {
                //   };
              );
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
    calls.current->Array.map(x => handleConnection(Some(x)))->ignore;

    Js.log2(myConn, incoming);
    None;
  });

  React.useEffect2(
    () => {
      open Peer;

      // switch (myConn.current) {
      // | Some(i) => i->Connection.send(value)->ignore
      // | None => ()
      // };

      let send = (conn, value) => conn->Connection.send(value)->ignore;

      switch (incoming.current) {
      | Some(i) => i->Connection.send({patientId, canvas})->ignore
      | None => ()
      };

      calls.current->Array.map(c => send(c, {patientId, canvas}))->ignore;

      None;
    },
    (patientId, canvas),
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
           onChange={data => setCanvas(_ => data)}
           data=canvas
         />
       </div>
     | _ => React.null
     }}
  </div>;
};
