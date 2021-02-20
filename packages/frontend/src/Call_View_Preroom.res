open WebRTC
@react.component
let make = (~stream, ~media, ~setMedia, ~onJoin, ~loading) =>
  <div className="w-full h-screen flex">
    <div className="shadow-lg m-24 flex  flex-wrap  items-center px-24 py-8 w-full">
      <div className="w-2/3 flex h-2/3 items-center justify-center">
        <div
          className="shadow-xl rounded-xl  overflow-hidden border border-gray h-full w-full flex items-center justify-center bg-black ">
          {!media.video
            ? <div className="bg-black w-full h-full flex items-center justify-center">
                <div className="text-3xl text-white">
                  <Text> j`Twoja kamera jest wyłączona` </Text>
                </div>
              </div>
            : <video
                ref={ReactDOM.Ref.callbackDomRef(el => WebRTC.setVideo(el, stream, media.video))}
                style={ReactDOM.Style.make(~transform="scale(-1, 1)", ())}
                className="transform w-full"
              />}
        </div>
      </div>
      <div className="w-1/3 flex flex-col items-center justify-center">
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Video size="36" /> </div>
          <Switch checked=media.video onChange={value => setMedia(SetVideo(value))} />
        </div>
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Mic size="36" /> </div>
          <Switch checked=media.audio onChange={value => setMedia(SetAudio(value))} />
        </div>
      </div>
      <div className="w-full  flex justify-center">
        <Button.CTA onClick={_ => onJoin()} loading>
          <Text> j`Dołącz do spotkania` </Text>
        </Button.CTA>
      </div>
    </div>
  </div>
