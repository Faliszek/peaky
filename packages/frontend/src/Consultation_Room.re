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

let useConsultation = (~peer, ~userIds, ~localStream, ~setStreams, ~streams) => {
  React.useEffect0(() => {
    let call = () =>
      if (streams->Array.size == userIds->Array.size) {
        ();
      } else {
        userIds
        ->Array.map(userId => {peer->Peer.call(userId, localStream)})
        ->ignore;
      };

    call();

    peer->Peer.onCall("error", _err => {call()});
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

module Meeting = {
  [@react.component]
  let make =
      (
        ~dataMyId,
        ~callerId,
        ~userIds,
        ~localStream,
        ~media,
        ~setMedia,
        ~peer,
        ~dataPeer,
        ~dataUserIds,
      ) => {
    let (streams, setStreams) = React.useState(_ => [||]);

    useConsultation(~userIds, ~localStream, ~setStreams, ~peer, ~streams);
    <div>
      <div className="flex w-full h-screen  overflow-hidden">
        <div className="w-1/2 flex items-center justify-center gap-4 flex-col">
          {streams
           ->Array.map(stream => <Video key={stream##id} stream />)
           ->React.array}
        </div>
        <div
          className="w-1/2 flex items-center justify-center overflow-y-scroll">
          <Consultation_Room_PatientView
            callerId
            myId=dataMyId
            userIds=dataUserIds
            peer=dataPeer
          />
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
            onClick={_ => peer->Peer.disconnect}
            icon={<Icons.Phone size="16" />}
          />
        </div>
      </div>
    </div>;
  };
};

type view =
  | Room
  | Consulting;
[@react.component]
let make = (~id) => {
  let query = ConsultationsQuery.use(~fetchPolicy=NetworkOnly, {id: id});

  let (stream, media, setMedia) = WebRTC.use();

  let (peer, setPeer) = React.useState(_ => None);
  let (dataPeer, setDataPeer) = React.useState(_ => None);

  let (view, setView) = React.useState(_ => Room);
  React.useEffect3(
    () => {
      switch (query, dataPeer) {
      | ({data: Some({me})}, None) =>
        setDataPeer(_ =>
          Some(
            Peer.make(
              "data" ++ me.id,
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
          )
        )

      | _ => ()
      };
      switch (query, peer) {
      | ({data: Some({me})}, None) =>
        setPeer(_ =>
          Some(
            Peer.make(
              "media" ++ me.id,
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
          )
        )

      | _ => ()
      };
      None;
    },
    (query.data, peer, dataPeer),
  );

  switch (query, dataPeer, peer) {
  | ({loading: true}, _, _) =>
    <div className="flex items-center justify-center w-full h-screen">
      <Spinner />
    </div>
  | (
      {data: Some({me, consultation: Some({userIds, callerId})})},
      Some(dataPeer),
      Some(peer),
    ) =>
    let myId = me.id;
    let dataMyId = "data" ++ me.id;

    let mediaUserIds =
      userIds
      ->Array.concat([|callerId|])
      ->Array.keep(u => u != myId)
      ->Array.map(u => "media" ++ u);

    let dataUserIds =
      userIds
      ->Array.concat([|callerId|])
      ->Array.keep(u => u != myId)
      ->Array.map(u => "data" ++ u);

    switch (view) {
    | Room =>
      <Call_View_Preroom
        stream
        media
        setMedia
        onJoin={_ => setView(_ => Consulting)}
        loading=false
      />
    | Consulting =>
      <Meeting
        dataMyId
        callerId
        localStream=stream
        media
        setMedia
        peer
        userIds=mediaUserIds
        dataPeer
        dataUserIds
      />
    };

  | _ => React.null
  };
};
