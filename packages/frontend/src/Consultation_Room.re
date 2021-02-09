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
  let make = (~myId, ~callerId, ~userIds, ~localStream, ~media, ~setMedia) => {
    // let myId = "data" ++ myId;
    Js.log(userIds);
    let userId =
      userIds
      ->Array.concat([|callerId|])
      ->Array.keep(u => u != myId)
      ->Array.get(0)
      ->Option.map(u => "data" ++ u)
      ->Option.getWithDefault("-");
    let peer =
      React.useRef(
        Peer.make(
          "data" ++ myId,
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

    let myConn = React.useRef(None);
    let incoming = React.useRef(None);
    let (value, setValue) = React.useState(_ => "dupa");

    React.useEffect0(() => {
      open Peer;
      // make(
      //   ~peer=peer.current,
      //   ~myVariable=value,
      //   ~userId,
      //   ~myConn=myConn.current,
      //   ~incoming=incoming.current,
      // )

      myConn.current =
        Some(peer.current->connect(userId, {serialization: "none"}));

      switch (myConn.current) {
      | Some(myConn) =>
        myConn->Connection.onOpen("open", () =>
          myConn->Connection.send(value)
        )

      | None => ()
      };

      peer.current
      ->onConnection("connection", conn => {
          incoming.current = Some(conn);
          incoming.current
          ->Option.map(i =>
              i->Connection.onData("data", data => {
                // Will print 'this is a test'
                Js.log2("ON RECEIVE", data);
                setValue(_ => data);
              })
            )
          ->ignore;
        });

      // peer.on('connection', function(conn) {

      //   incoming = conn;

      None;
    });

    Js.log2(myConn, incoming);

    React.useEffect1(
      () => {
        open Peer;
        myConn.current->Option.map(i => i->Connection.send(value))->ignore;
        incoming.current->Option.map(i => i->Connection.send(value))->ignore;
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

  switch (query) {
  | {loading: true} =>
    <div className="flex items-center justify-center w-full h-screen">
      <Spinner />
    </div>
  | {data: Some({me, consultation: Some({userIds, callerId})})} =>
    <Meeting myId={me.id} userIds callerId localStream=stream media setMedia />
  | _ => React.null
  };
};
