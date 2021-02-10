open WebRTC;
open Peer;

let useVideoCall =
    (
      ~isPatient,
      ~doctorPeerId,
      ~patientPeerId,
      ~localStream,
      ~setRemote,
      ~peer,
    ) => {
  Peer.(
    React.useEffect0(() => {
      if (isPatient) {
        peer->Peer.call(doctorPeerId, localStream);

        peer->Peer.onCall("error", _err => {
          peer->Peer.call(doctorPeerId, localStream)
        });

        peer->onCall("call", call => {
          call->Call.answer(localStream);
          call->Call.onStream("stream", remote => {
            remote
            ->Js.Nullable.toOption
            ->Option.map(r => setRemote(_ => Some(r)))
            ->ignore
          });
        });
      } else {
        peer->Peer.call(patientPeerId, localStream);
        peer->Peer.onCall("error", _err => {
          peer->Peer.call(patientPeerId, localStream)
        });

        peer->onCall("call", call => {
          call->Call.answer(localStream);
          call->Call.onStream("stream", remote => {
            remote
            ->Js.Nullable.toOption
            ->Option.map(r => setRemote(_ => Some(r)))
            ->ignore
          });
        });
      };

      None;
    })
  );
};

let close = [%bs.raw {|
  function() {
    window.close();
  }
|}];
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
      make(
        peerId,
        {
          port: "9000",
          host: "localhost",
          path: "/calls",
          debug: 1,
          pingInterval: 5000,
          config: {
            iceServers: iceServers,
          },
        },
      ),
    );

  let (ended, setEnded) = React.useState(_ => false);
  useVideoCall(
    ~peer=peer.current,
    ~setRemote,
    ~localStream,
    ~doctorPeerId,
    ~patientPeerId,
    ~isPatient,
  );

  let localClassName =
    remote->Option.isSome
      ? "w-64 h-auto absolute bottom-12 left-4 shadow-xl border-2 border-gray rounded-xl"
      : "";
  let remoteClassName = remote->Option.isSome ? "w-full h-full" : "";

  switch (isPatient, ended) {
  | (true, true) =>
    <div
      className="bg-black w-screen h-screen flex items-center justify-center">
      <div className="text-3xl text-white">
        <Text> {j|Spotkanie zostało zakończone|j} </Text>
      </div>
    </div>

  | _ =>
    <div className="flex items-center justify-center h-screen">
      {switch (remote) {
       | Some(remote) =>
         <video
           ref={ReactDOM.Ref.callbackDomRef(el =>
             WebRTC.setVideo(el, remote, true)
           )}
           style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
           className=Cn.(
             "transform rounded-xl border-2 border-gray bg-black"
             + remoteClassName
           )
         />
       | None => React.null
       }}
      <video
        ref={ReactDOM.Ref.callbackDomRef(el =>
          WebRTC.setVideo(el, localStream, media.video)
        )}
        style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
        className=Cn.("transform rounded-xl" + localClassName)
      />
      {remote->Option.isNone
         ? <div
             className="bg-black opacity-50 text-3xl text-white w-full h-full flex items-center justify-center absolute top-0 left-0">
             <Text>
               {j|Twój rozmówca jeszcze nie dołączył do rozmowy|j}
             </Text>
           </div>
         : React.null}
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
          onClick={_ => {
            isPatient ? setEnded(_ => true) : Router.push(Calendar)
          }}
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
    </div>
  };
};
