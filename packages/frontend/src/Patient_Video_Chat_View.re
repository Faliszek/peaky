open Patient;
open WebRTC;
let patient = {
  id: 1,
  firstName: {j|Adam|j},
  lastName: {j|Smith|j},
  disease: {j|Depresja|j},
  condition: {j|Dobry|j},
  avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),

  phoneNumber: {j|+48 674 300 232|j},
  lastVisit: None,
};

[@react.component]
let make = (~id as _id) => {
  let videoElement = React.useRef(Js.Nullable.null);

  let (media, setMedia) = WebRTC.use(~videoElement);

  Js.log(media);
  <div className="flex flex-col h-screen w-full relative">
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
    </div>
  </div>;
};
