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

module Meeting = {
  [@react.component]
  let make =
      (~myId, ~callerId, ~userIds, ~localStream, ~media, ~setMedia, ~peer) => {
    // let myId = "data" ++ myId;
    Js.log(userIds);
    let userId =
      userIds
      ->Array.concat([|callerId|])
      ->Array.keep(u => u != myId)
      ->Array.get(0)
      ->Option.map(u => "data" ++ u)
      ->Option.getWithDefault("-");

    Js.log2("ALWAYS HAVE PEER", peer);
    let myConn = React.useRef(None);
    let incoming = React.useRef(None);
    let (value, setValue) = React.useState(_ => "dupa");

    React.useEffect0(() => {
      open Peer;

      myConn.current = Some(peer->connect(userId));

      peer->onConnection("connection", conn => {
        incoming.current = Some(conn);
        switch (incoming.current) {
        | Some(incoming) =>
          incoming
          ->Connection.onOpen("open", _ => {
              // Will print 'this is a test'
              incoming->Connection.onData("data", data => {
                Js.log2("ON RECEIVE", data);
                setValue(_ => data);
              })
            })
          ->ignore
        | None => ()
        };
      });

      switch (myConn.current) {
      | Some(myConn) =>
        myConn->Connection.onOpen("open", () => {
          //     // myConn->Connection.send(value)
          myConn->Connection.onData("data", data => {
            Js.log2("ON RECEIVE", data);
            setValue(_ => data);
          });
          Js.log("Connection opened");
        })
      | None => ()
      };

      Js.log2(myConn, incoming);
      None;
    });

    React.useEffect1(
      () => {
        open Peer;
        // myConn.current->Option.map(i => i->Connection.send(value))->ignore;
        switch (incoming.current) {
        | Some(i) => i->Connection.send(value)->ignore
        | None => ()
        };

        switch (myConn.current) {
        | Some(i) => i->Connection.send(value)->ignore
        | None => ()
        };
        None;
      },
      [|value|],
    );

    <div>
      {{
         "Call from " ++ myId ++ "To " ++ userId;
       }
       ->React.string}
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
  // let (view, setView) = React.useState(_ => Room);

  let (stream, media, setMedia) = WebRTC.use();

  let peer = React.useRef(None);

  React.useEffect2(
    () => {
      Js.log2("QUERY rerended", query.data);
      switch (query, peer.current) {
      | ({data: Some({me})}, None) =>
        peer.current =
          Some(
            Peer.make(
              "data" ++ me.id,
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
          )

      | _ => ()
      };
      None;
    },
    (query.data, peer.current),
  );

  switch (query, peer.current) {
  | ({loading: true}, _) =>
    <div className="flex items-center justify-center w-full h-screen">
      <Spinner />
    </div>
  | (
      {data: Some({me, consultation: Some({userIds, callerId})})},
      Some(peer),
    ) =>
    <Meeting
      myId={me.id}
      userIds
      callerId
      localStream=stream
      media
      setMedia
      peer
    />
  | _ => React.null
  };
};
