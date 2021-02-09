open WebRTC;

module ConsultationsQuery = [%graphql
  {|
query Consultation($id: String!) {
  me {
    id
  }
  users {
    id
    firstName
    lastName
  }
  consultation(id: $id){
    id
    callerId
    userIds
  }
}
|}
];

let useData =
    (
      ~myId,
      ~callerId,
      ~peer,
      ~userIds,
      ~onReceiveData,
      ~data: string,
      ~patientId,
    ) => {
  let incomingCall = React.useRef(None);
  let myConnection = React.useRef(None);
  let patientId = patientId->Option.getWithDefault("");

  Peer.(
    React.useEffect0(() => {
      let userId = userIds->Array.keep(u => u != myId)->Array.getExn(0);

      Js.log2(myId, userId);

      let call = peer->Peer.connect(userId, {serialization: "none"});

      call->Connection.onOpen("open", () => {
        Js.log2("User resond", userId);

        call->Connection.onData("data", data => {onReceiveData(data)});
      });

      incomingCall.current = Some(call);

      peer->Peer.onConnection("connection", conn => {
        Js.log2("SOMEONE JOINED", conn);

        myConnection.current = Some(conn);

        conn->Connection.onOpen("open", () => {
          Js.log2("Open connection with", conn.peer);
          conn->Connection.onData("data", data => {onReceiveData(data)});
        });
      });

      peer->Peer.onError("error", err => Js.log(err));

      None;
    })
  );

  React.useEffect1(
    () => {
      open Peer;
      Js.log3("Will send ", myConnection, incomingCall);
      incomingCall.current
      ->Option.map(i => i->Connection.send(patientId))
      ->ignore;
      // connections.current
      // ->Array.forEach(c => {
      //     ->Connection.send(patientId->Option.getWithDefault(""))
      //   });
      None;
    },
    [|patientId|],
  );
};

module PatientData = {
  [@react.component]
  let make =
      (~patientId, ~callerId, ~userIds, ~peer, ~myId, ~color, ~setPatientId) => {
    let (width, setWidth) = React.useState(_ => None);
    let (height, setHeight) = React.useState(_ => None);
    let (data, setData) = React.useState(_ => "");

    // useData(
    //   ~myId,
    //   ~callerId,
    //   ~userIds,
    //   ~peer,
    //   ~onReceiveData=
    //     data => {
    //       Js.log2(
    //         "RECEIVE",
    //         data,
    //         // setPatientId(Some(data.patientId));
    //         // setData(_ => data.data);
    //       )
    //     },
    //   ~data,
    //   ~patientId,
    // );

    React.useEffect1(
      () => {
        if (myId == callerId) {
          setData(_ => "")->ignore;
        } else {
          ();
        };

        None;
      },
      [|patientId|],
    );

    let amICaller = myId != callerId;
    <div className="w-full h-full relative">
      <div
        ref={ReactDOM.Ref.callbackDomRef(el =>
          el
          ->Js.Nullable.toOption
          ->Option.map(el => {
              Timeout.set(
                () => {
                  setWidth(_ => Some(el->HTMLElement.offsetWidth));
                  setHeight(_ => Some(el->HTMLElement.offsetHeight));
                },
                1000,
              )
            })
          ->ignore
        )}>
        {switch (amICaller, patientId) {
         | (_, Some(patientId)) =>
           <Patient_Details_View id=patientId callMode=true />
         | (true, _) =>
           <Text> {j|Prowadzący nie wybrał jeszcze pacjenta|j} </Text>

         | _ => React.null
         }}
      </div>
      <div className="absolute w-full h-full top-0 left-0">
        {switch (height, width, patientId) {
         | (Some(height), Some(width), Some(patientId)) =>
           <CanvasDraw
             onChange={v => {
               let data = v.getSaveData();
               setData(_ => data);
             }}
             gridColor="transparent"
             backgroundColor="transparent"
             hideGrid=true
             brushColor=color
             canvasHeight=height
             canvasWidth=width
             brushRadius=4.0
             saveData=data
             immediateLoading=true
           />
         | _ => React.null
         }}
      </div>
    </div>;
  };
};

module PatientView = {
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

    let (patientId, setPatientId) = React.useState(_ => None);
    let (color, setColor) = React.useState(_ => "rgb(96, 165, 250)");

    let (visible, setVisible) = React.useState(_ => false);

    let callerId = "data" ++ callerId;
    let userIds = userIds->Array.map(u => "data" ++ u);

    let userIds =
      userIds->Array.concat([|callerId|])->Array.keep(u => u != myId);

    <div className="w-full h-screen flex items-center">
      {switch (query) {
       | {loading: true} => <Spinner />
       | {data: Some({patients})} =>
         <div className="h-full py-8 px-4 w-full">
           <div
             className="w-full flex gap-8 justify-between shadow-lg sticky border-bottom border-gray-300 top-0 p-4 rounded-xl z-20 bg-white">
             //  {callerId == myId  ?

               <div className="flex gap-8 justify-between">
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
                     setPatientId(_ => patient.value->Option.map(x => x.value))
                   }>
                   <Text> {j|Wybierz|j} </Text>
                 </Button.CTA>
               </div>
               // : React.null}
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
           <PatientData
             peer
             patientId
             color
             myId
             userIds
             callerId
             setPatientId={v => setPatientId(_ => v)}
           />
         </div>
       | _ => React.null
       }}
    </div>;
  };
};

module Meeting = {
  module Video = {
    [@react.component]
    let make = (~stream) => {
      <video
        ref={ReactDOM.Ref.callbackDomRef(el =>
          WebRTC.setVideo(el, stream, true)
        )}
        style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
        className="shadow-xl rounded-xl flex-1 transform border-2 border-gray bg-black"
      />;
    };
  };

  [@react.component]
  let make = (~myId, ~callerId, ~userIds, ~localStream, ~media, ~setMedia) => {
    let myId = "data" ++ myId;

    let peer =
      React.useRef(
        Peer.make(
          myId,
          {
            port: "9000",
            host: "localhost",
            path: "/calls",
            debug: 3,
            pingInterval: 5000,

            config: {
              iceServers: Peer.iceServers,
            },
          },
        ),
      );

    let (streams, setStreams) = React.useState(_ => [||]);

    // useConsultation(
    //   ~myId,
    //   ~callerId,
    //   ~userIds,
    //   ~localStream,
    //   ~setStreams,
    //   ~peer=peer.current,
    //   ~streams,
    // );
    // React.useEffect1(
    //   () => {
    //     Js.log2("STREAMS", streams);
    //     None;
    //   },
    //   [|streams|],
    // );
    <>
      <div className="flex w-full h-screen  ">
        <div className="w-1/2 flex items-center justify-center gap-4 flex-col">
          {streams->Array.map(stream => <Video stream />)->React.array}
        </div>
        <div className="w-1/2 flex items-center justify-center">
          <PatientView callerId myId userIds peer={peer.current} />
        </div>
      </div>
      <div
        className="w-64 h-32 fixed left-40 ml-12 top-12 bg-black flex items-center rounded-xl justify-center">
        <video
          style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
          className="transform rounded-xl border-2 border-gray bg-black"
          ref={ReactDOM.Ref.callbackDomRef(el =>
            WebRTC.setVideo(el, localStream, true)
          )}
        />
        <div className="flex justify-around gap-4 absolute bottom-2 w-full">
          <Button.CallButton
            className="bg-white  text-gray-600 hover:bg-gray-100"
            onClick={_ => setMedia(SetAudio(!media.audio))}
            icon={
              media.audio
                ? <Icons.Mic size="16" /> : <Icons.MicOff size="16" />
            }
          />
          <Button.CallButton
            className="bg-white text-gray-600  hover:bg-gray-100"
            onClick={_ => setMedia(SetVideo(!media.video))}
            icon={
              media.video
                ? <Icons.Video size="16" /> : <Icons.VideoOff size="16" />
            }
          />
          <Button.CallButton
            className="bg-red-400 text-white  hover:bg-red-300"
            onClick={_ => peer.current->Peer.disconnect}
            icon={<Icons.Phone size="16" />}
          />
        </div>
      </div>
    </>;
  };
};

type view =
  | Room
  | Meeting;
[@react.component]
let make = (~id) => {
  let query = ConsultationsQuery.use({id: id});
  let (view, setView) = React.useState(_ => Room);

  let (stream, media, setMedia) = WebRTC.use();

  switch (query) {
  | {loading: true} =>
    <div className="flex items-center justify-center w-full h-screen">
      <Spinner />
    </div>
  | {data: Some({me, consultation: Some({userIds, callerId})})} =>
    switch (view) {
    | Room =>
      <Call_View_Preroom
        stream
        media
        setMedia
        onJoin={_ => setView(_ => Meeting)}
        loading=false
      />
    | Meeting =>
      <Meeting
        myId={me.id}
        userIds
        callerId
        localStream=stream
        media
        setMedia
      />
    }

  | _ => React.null
  };
};
