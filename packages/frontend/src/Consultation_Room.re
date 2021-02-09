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

let useShareDate = () => {};

module Meeting = {
  [@react.component]
  let make =
      (~myId, ~callerId, ~userIds, ~localStream, ~media, ~setMedia, ~peer) => {
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
    let (value, setValue) = React.useState(_ => "dupa");

    React.useEffect0(() => {
      open Peer;

      let handleConnection = c => {
        switch (c) {
        | Some(c) =>
          c
          ->Connection.onOpen("open", _ => {
              // Will print 'this is a test'
              c->Connection.onData("data", data => {
                Js.log2("ON RECEIVE", data);
                if (data != value) {
                  setValue(v => v == data ? v : data);
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

      calls.current = userIds->Array.map(peer->connect);
      calls.current->Array.map(x => handleConnection(Some(x)))->ignore;

      Js.log2(myConn, incoming);
      None;
    });

    React.useEffect1(
      () => {
        open Peer;

        // switch (myConn.current) {
        // | Some(i) => i->Connection.send(value)->ignore
        // | None => ()
        // };

        let send = (conn, value) => conn->Connection.send(value)->ignore;

        switch (incoming.current) {
        | Some(i) => i->Connection.send(value)->ignore
        | None => ()
        };

        calls.current->Array.map(c => send(c, value))->ignore;

        None;
      },
      [|value|],
    );

    <div>
      {{
         "Call from " ++ myId ++ "To ";
       }
       ->React.string}
      {userIds->Array.map(s => s->React.string)->React.array}
      <Input placeholder={||} value onChange={v => setValue(_ => v)} />
      <Button onClick={_ => ()}> <Text> {j|Wyślij|j} </Text> </Button>
    </div>;
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
