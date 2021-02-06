type timeoutID;

[@bs.val] external setTimeout: (unit => unit, int) => timeoutID = "setTimeout";

[@bs.val] external clearTimeout: timeoutID => unit = "setTimeout";

module CopyLink = {
  let copy = [%raw
    {|function updateClipboard(newClip) {
  navigator.clipboard.writeText(newClip);
}|}
  ];
  [@react.component]
  let make = (~link) => {
    let (copied, setCopied) = React.useState(_ => false);

    React.useEffect1(
      () => {
        let timeout =
          setTimeout(
            () =>
              if (copied) {
                setCopied(_ => false);
              },
            2000,
          );

        Some(_ => clearTimeout(timeout));
      },
      [|copied|],
    );
    <div className="fixed bottom-12 right-36 mb-3">
      <Button.CTA
        type_=`ghost
        className="w-full flex items-center justify-center"
        onClick={_ => {
          setCopied(_ => true);
          copy(link);
        }}
        icon={
          copied
            ? <Icons.Check className="mr-4" />
            : <Icons.Link className="mr-4" />
        }>
        <Text> {copied ? {j|Skopiowano!|j} : {j|Skopiuj link|j}} </Text>
      </Button.CTA>
    </div>;
  };
};

module Preroom = {
  open WebRTC;
  [@react.component]
  let make = (~stream, ~media, ~setMedia, ~onJoin, ~loading) => {
    <div className="shadow-lg m-24 flex  flex-wrap  items-center p-24">
      <div className="w-2/3">
        <div
          className="shadow-xl rounded-xl  overflow-hidden border border-gray h-96">
          {!media.video
             ? <div
                 className="bg-black w-full h-full flex items-center justify-center">
                 <div className="text-3xl text-white">
                   <Text> {|Twoja kamera jest wyłączona|} </Text>
                 </div>
               </div>
             : <video
                 ref={ReactDOM.Ref.callbackDomRef(el =>
                   WebRTC.setVideo(el, stream, media.video)
                 )}
                 style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
                 className="transform"
               />}
        </div>
      </div>
      <div className="w-1/3 flex flex-col items-center justify-center">
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Video size="36" /> </div>
          <Switch
            checked={media.video}
            onChange={value => setMedia(SetVideo(value))}
          />
        </div>
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Mic size="36" /> </div>
          <Switch
            checked={media.audio}
            onChange={value => setMedia(SetAudio(value))}
          />
        </div>
      </div>
      <div className="w-full pt-16 flex justify-center">
        <Button.CTA onClick={_ => onJoin()} loading>
          <Text> {j|Dołącz do spotkania|j} </Text>
        </Button.CTA>
      </div>
    </div>;
  };
};

module PeerModule = {
  type t = {id: string};
  type mediaStream = Js.Nullable.t(WebRTC.Media.srcObject);

  module Call = {
    type call;
    [@bs.send] external answer: (call, mediaStream) => unit = "answer";
    [@bs.send]
    external onStream: (call, string, mediaStream => unit) => unit = "on";
  };

  type ice = {
    urls: string,
    credential: option(string),
    username: option(string),
  };

  type config = {iceServers: array(ice)};
  type options = {
    // id: string,
    host: string,
    path: string,
    port: string,
    debug: int,
    config,
  };
  [@bs.module "peerjs"] [@bs.new]
  external make: (string, options) => t = "default";

  [@bs.send] external onOpen: (t, string, string => unit) => unit = "on";

  [@bs.send] external onCall: (t, string, Call.call => unit) => unit = "on";

  [@bs.send] external onError: (t, string, string => unit) => unit = "on";

  [@bs.send] external call: (t, string, mediaStream) => unit = "call";
};

type view =
  | Preroom
  | Meeting;

let iceServers: array(PeerModule.ice) = [|
  {urls: "stun:stun.l.google.com:19302", credential: None, username: None},
  {urls: "stun:stun1.l.google.com:19302", credential: None, username: None},
  {urls: "stun:stun2.l.google.com:19302", credential: None, username: None},
  {urls: "stun:stun3.l.google.com:19302", credential: None, username: None},
|];

module Meeting = {
  open WebRTC;
  [@react.component]
  let make =
      (
        ~media,
        ~setMedia,
        ~callId,
        ~patientId,
        ~doctorId,
        ~localStream,
        ~isPatient,
      ) => {
    let doctorPeerId = doctorId->Js.String2.replace("-", "");
    let patientPeerId = patientId->Js.String2.replace("-", "");
    let (remote, setRemote) = React.useState(_ => None);
    let peerId = isPatient ? patientPeerId : doctorPeerId;
    let peer =
      React.useRef(
        PeerModule.make(
          peerId,
          {
            port: "9000",
            host: "localhost",
            path: "/calls",
            debug: 1,

            config: {
              iceServers: iceServers,
            },
          },
        ),
      );

    React.useEffect0(() => {
      let callingId = if (isPatient) {doctorPeerId} else {patientPeerId};

      peer.current->PeerModule.call(callingId, localStream);

      peer.current
      ->PeerModule.onCall("call", call => {
          call->PeerModule.Call.answer(localStream);
          call->PeerModule.Call.onStream("stream", remote => {
            remote
            ->Js.Nullable.toOption
            ->Option.map(r => setRemote(_ => Some(r)))
            ->ignore
          });
        });
      None;
    });

    <div className="flex items-center justify-center h-screen">
      <video
        ref={ReactDOM.Ref.callbackDomRef(el =>
          WebRTC.setVideo(el, localStream, media.video)
        )}
        style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
        className="transform rounded-xl flex-1 w-1/2"
      />
      {switch (remote) {
       | Some(remote) =>
         <video
           ref={ReactDOM.Ref.callbackDomRef(el =>
             WebRTC.setVideo(el, remote, true)
           )}
           style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
           className="transform rounded-xl flex-1 w-1/2"
         />
       | None =>
         <div className="flex-1 w-1/2"> "No Video :("->React.string </div>
       }}
      <div className="fixed bottom-24 flex  gap-4">
        <Button.Round
          className="bg-white  text-gray-600 hover:bg-gray-100"
          onClick={_ => setMedia(SetAudio(!media.audio))}
          icon={
            media.audio ? <Icons.Mic size="36" /> : <Icons.MicOff size="36" />
          }
        />
        <Button.Round
          className="bg-white text-gray-600  hover:bg-gray-100"
          onClick={_ => setMedia(SetVideo(!media.video))}
          icon={
            media.video
              ? <Icons.Video size="36" /> : <Icons.VideoOff size="36" />
          }
        />
        <Button.Round
          className="bg-red-400 text-white  hover:bg-red-300"
          onClick={_ => ()}
          icon={<Icons.Phone size="36" />}
        />
      </div>
      {!isPatient
         ? <>
             <Patient_Add_Event
               patientId={isPatient ? None : Some(patientId)}
             />
             <CopyLink
               link={j|http://localhost:8080/calls/$callId/$doctorId/$patientId|j}
             />
           </>
         : React.null}
    </div>;
  };
};
[@react.component]
let make = (~id as callId, ~patientId, ~doctorId, ~isPatient) => {
  // open WebRTC.MediaDevices.Constraints;

  let (stream, media, setMedia) = WebRTC.use();

  let (mutation, result) = Call_CreateRoom_Mutation.Mutation.use();

  let (view, setView) = React.useState(_ => Preroom);

  switch (isPatient) {
  //DOCTOR
  | false =>
    let userId = Auth.getUserId();

    <div className="flex flex-col h-screen w-full relative">
      {switch (view) {
       | Preroom =>
         <Preroom
           stream
           media
           setMedia
           loading={result.loading}
           onJoin={_ => {
             mutation({doctorId: userId, patientId})
             ->Request.onFinish(
                 ~onError=_ => (),
                 ~onOk=
                   ({createRoom}) => {
                     switch (createRoom) {
                     | Some(_) => setView(_ => Meeting)
                     | None => ()
                     }
                   },
               )
           }}
         />
       | Meeting =>
         <Meeting
           callId
           doctorId
           isPatient
           localStream=stream
           media
           patientId
           setMedia
         />
       }}
    </div>;

  | true =>
    <div className="flex flex-col h-screen w-full relative">
      {switch (view) {
       | Preroom =>
         <Preroom
           loading=false
           stream
           media
           setMedia
           onJoin={_ => {setView(_ => Meeting)}}
         />
       | Meeting =>
         <Meeting
           callId
           doctorId
           isPatient
           localStream=stream
           media
           patientId
           setMedia
         />
       }}
    </div>
  };
};
