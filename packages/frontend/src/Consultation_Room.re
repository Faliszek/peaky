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

let useConsultation =
    (~myId, ~callerId, ~peer, ~userIds, ~localStream, ~setStreams, ~streams) => {
  React.useEffect0(() => {
    Js.log2("Mounted", myId);
    let userIds =
      userIds->Array.concat([|callerId|])->Array.keep(u => u != myId);

    let call = () =>
      if (streams->Array.size == userIds->Array.size) {
        ();
      } else {
        userIds
        ->Array.map(userId => {
            Js.log2("calling to", userId);
            peer->Peer.call(userId, localStream);
          })
        ->ignore;
      };

    call();

    peer->Peer.onCall("error", _err => call());
    peer->Peer.onCall("call", call => {
      call->Peer.Call.answer(localStream);
      call->Peer.Call.onStream("stream", remoteStream => {
        switch (remoteStream->Js.Nullable.toOption) {
        | Some(remoteStream) =>
          setStreams(streams =>
            if (streams
                ->Array.keep(x => x##id == remoteStream##id)
                ->Array.get(0)
                ->Option.isSome) {
              streams;
            } else {
              streams->Array.concat([|remoteStream|]);
            }
          )
        | None => Js.log("no Stream")
        }
      });
    });

    None;
  });
};

let useData = (~myId, ~callerId, ~peer, ~userIds) => {
  Peer.(
    React.useEffect0(() => {
      let userIds =
        userIds->Array.concat([|callerId|])->Array.keep(u => u != myId);

      userIds
      ->Array.map(userId => {
          Js.log2("SETTING UP CONNECTION for", userId);
          peer->onConnection("connection", x => {
            x->Connection.onOpen("open", () => {
              x->Connection.onData("data", data =>
                Js.log2("RECEIVE FUCKING DATA", data)
              )
            });

            x->Connection.send("dupa");
          });

          let incomingConnection = peer->connect(userId);

          incomingConnection->Connection.onOpen("open", () => {
            incomingConnection->Connection.send("dupa")
          });

          incomingConnection;
        })
      ->ignore;
      None;
    })
  );
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

  // let d =
  //   Obj.magic(
  //     Js.Json.stringifyAny({
  //       "lines": [|
  //         {
  //           "points": [|
  //             {"x": 147.3007884391191, "y": 225.43386344836821},
  //             {"x": 147.3007884391191, "y": 225.43386344836821},
  //             {"x": 147.3007884391191, "y": 225.43386344836821},
  //             {"x": 149.84546070411582, "y": 224.42450597203526},
  //             {"x": 157.30787132407474, "y": 222.70076415586524},
  //             {"x": 168.08409881624166, "y": 221.41820272842315},
  //             {"x": 185.01440694056703, "y": 220.58784267765463},
  //             {"x": 225.00076712444866, "y": 220.13568492284585},
  //             {"x": 240.00015153165222, "y": 220.0603053620484},
  //             {"x": 272.0000112709399, "y": 220.0164469581163},
  //             {"x": 284.0000028177353, "y": 220.0082234809891},
  //             {"x": 331.00694535072813, "y": 218.4082158492491},
  //             {"x": 357.02403407359037, "y": 216.75910482113866},
  //             {"x": 407.1768371840599, "y": 208.0525157801515},
  //             {"x": 407.1768371840599, "y": 208.0525157801515},
  //           |],
  //           "brushColor": "rgb(96, 165, 250)",
  //           "brushRadius": 4,
  //         },
  //       |],
  //       "width": 1168,
  //       "height": 600,
  //     }),
  //   );

  [@react.component]
  let make = (~callerId, ~myId, ~userIds) => {
    let query = Query.use();
    let patient = Select.use();

    let (patientId, setPatientId) = React.useState(_ => None);
    let (color, setColor) = React.useState(_ => "rgb(96, 165, 250)");

    let (visible, setVisible) = React.useState(_ => false);

    let (drawer, setDrawer) = React.useState(_ => None);

    let (width, setWidth) = React.useState(_ => None);
    let (height, setHeight) = React.useState(_ => None);

    let (data, setData) = React.useState(_ => "");

    let myId = "data" ++ myId;
    let callerId = "data" ++ callerId;
    let userIds = userIds->Array.map(u => "data" ++ u);

    let userIds =
      userIds->Array.concat([|callerId|])->Array.keep(u => u != myId);

    let peer =
      React.useRef(
        Peer.make(
          myId,
          {
            port: "9000",
            host: "localhost",
            path: "/calls",
            debug: 0,
            pingInterval: 5000,

            config: {
              iceServers: Peer.iceServers,
            },
          },
        ),
      );
    Js.log3(myId, callerId, userIds);
    useData(~myId, ~callerId, ~userIds, ~peer=peer.current);

    React.useEffect1(
      () => {
        open CanvasDraw;
        switch (drawer) {
        | Some(drawer) => Js.log2("change triggered", drawer.getSaveData())
        | None => ()
        };
        None;
      },
      [|drawer|],
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
           {switch (patientId) {
            | Some(value) =>
              <div className="w-full h-full relative">
                <div
                  ref={ReactDOM.Ref.callbackDomRef(el =>
                    el
                    ->Js.Nullable.toOption
                    ->Option.map(el => {
                        setWidth(_ => Some(el->HTMLElement.offsetWidth));
                        setHeight(_ => Some(el->HTMLElement.offsetHeight));
                      })
                    ->ignore
                  )}>
                  <Patient_Details_View id=value callMode=true />
                </div>
                <div className="absolute w-full h-full top-0 left-0">
                  <CanvasDraw
                    onChange={v => {
                      Js.log2("change triggered", v);
                      setDrawer(_ => Some(v));
                      drawer
                      ->Option.map(d =>
                          setData(_ => d.getSaveData->CanvasDraw.dataToString)
                        )
                      ->ignore;
                    }}
                    gridColor="transparent"
                    backgroundColor="transparent"
                    hideGrid=true
                    brushColor=color
                    canvasHeight={height->Option.getWithDefault(0.0)}
                    canvasWidth={width->Option.getWithDefault(0.0)}
                    brushRadius=4.0
                    saveData=data
                  />
                </div>
              </div>
            | None => React.null
            }}
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
    let peer =
      React.useRef(
        Peer.make(
          myId,
          {
            port: "9000",
            host: "localhost",
            path: "/calls",
            debug: 1,
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
          <PatientView callerId myId userIds />
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
