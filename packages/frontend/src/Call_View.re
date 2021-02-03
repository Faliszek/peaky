module Peer = {
  type t;

  [@bs.module "peerjs"] [@new] external make: unit => t = "Peer";
};

module Preroom = {
  open WebRTC;
  [@react.component]
  let make = (~media, ~setMedia, ~videoElement) => {
    <div className="shadow-lg m-24 flex  flex-wrap  items-center p-24">
      <div className="w-2/3">
        <div
          className="shadow-xl rounded-xl  overflow-hidden border border-gray h-96">
          {switch (media.video) {
           | On => React.null

           | Awaits
           | Off =>
             <div
               className="bg-black w-full h-full flex items-center justify-center">
               <div className="text-3xl text-white">
                 <Text>
                   {switch (media.video) {
                    | Off => {j|Twoja kamera jest wyłączona|j}
                    | Awaits => {j|Trwa oczekwianie na dane...|j}
                    | _ => ""
                    }}
                 </Text>
               </div>
             </div>
           }}
          <video
            ref={ReactDOM.Ref.domRef(videoElement)}
            style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
            className="transform"
          />
        </div>
      </div>
      <div className="w-1/3 flex flex-col items-center justify-center">
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Video size="36" /> </div>
          <Switch
            checked={media.video == On}
            loading={media.video == Awaits}
            onChange={value => setMedia(ToggleVideo(value))}
          />
        </div>
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Mic size="36" /> </div>
          <Switch
            loading={media.audio == Awaits}
            checked={media.audio == On}
            onChange={value => setMedia(ToggleAudio(value))}
          />
        </div>
      </div>
      <div className="w-full pt-16 flex justify-center">
        <Button.CTA> <Text> {j|Dołącz do spotkania|j} </Text> </Button.CTA>
      </div>
    </div>;
  };
};

[@react.component]
let make = (~id as _) => {
  open WebRTC.MediaDevices.Constraints;
  let videoElement = React.useRef(Js.Nullable.null);

  let (media, setMedia) = WebRTC.use(~videoElement);

  let constraints =
    React.useMemo2(
      () =>
        {
          audio: media.audio->WebRTC.toBool,
          video: media.video->WebRTC.toBool,
        },
      (media.audio, media.video),
    );

  let {stream}: WebRTC.UserMedia.hook = WebRTC.UserMedia.use(constraints);

  switch (stream->Js.Nullable.toOption) {
  | Some(stream) =>
    Js.log3(
      stream->WebRTC.MediaStream.getAudioTracks(),
      stream->WebRTC.MediaStream.getVideoTracks(),
      media,
    )
  | None => ()
  };

  <div className="flex flex-col h-screen w-full relative">
    <Preroom media setMedia videoElement />
  </div>;
};
