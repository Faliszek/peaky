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
      (~myId, ~callerId, ~userIds, ~localStream, ~media, ~setMedia, ~peer) => {
    <div>

        <div className="flex w-full h-screen  ">
          <div
            className="w-1/2 flex items-center justify-center gap-4 flex-col"
            // {streams->Array.map(stream => <Video stream />)->React.array}
          />
          <div className="w-1/2 flex items-center justify-center">
            <Consultation_Room_PatientView callerId myId userIds peer />
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
      // </div>;
      //   <Button onClick={_ => ()}> <Text> {j|Wyślij|j} </Text> </Button>
      //   <Input placeholder={||} value onChange={v => setValue(_ => v)} />
      //   {userIds->Array.map(s => s->React.string)->React.array}
      //    ->React.string}
      //    }
      //      "Call from " ++ myId ++ "To ";
      //   {{
      // <div>
  };
};

type view =
  | Room
  | Meeting;
[@react.component]
let make = (~id) => {
  let query = ConsultationsQuery.use({id: id});

  let (stream, media, setMedia) = WebRTC.use();

  let (peer, setPeer) = React.useState(_ => None);

  let (view, setView) = React.useState(_ => Meeting);

  React.useEffect2(
    () => {
      Js.log2("QUERY rerended", query.data);
      switch (query, peer) {
      | ({data: Some({me})}, None) =>
        setPeer(_ =>
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
      None;
    },
    (query.data, peer),
  );

  switch (query, peer) {
  | ({loading: true}, _) =>
    <div className="flex items-center justify-center w-full h-screen">
      <Spinner />
    </div>
  | (
      {data: Some({me, consultation: Some({userIds, callerId})})},
      Some(peer),
    ) =>
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
        peer
      />
    }

  | _ => React.null
  };
};
