open Patient;
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

type userExternalDeviceState = {
  loading: bool,
  on: bool,
};

type state = {
  video: userExternalDeviceState,
  audio: userExternalDeviceState,
};

type action =
  | ToggleVideo(userExternalDeviceState)
  | ToggleAudio(userExternalDeviceState);

let initialState = {
  video: {
    loading: false,
    on: false,
  },
  audio: {
    loading: false,
    on: false,
  },
};
let reducer = (state, action) =>
  switch (action) {
  | ToggleVideo(video) => {...state, video}
  | ToggleAudio(audio) => {...state, audio}
  };

let setVideo = [%raw
  {|
   function initVideo(video, mediaStream) { video.srcObject = mediaStream
    video.onloadedmetadata = function(e) {
    video.play()
  }
  }
  |}
];

[@react.component]
let make = (~id) => {
  let {avatar, lastName, firstName} = patient;

  //   let name = firstName ++ " " ++ lastName;

  let (state, dispatch) = React.useReducer(reducer, initialState);

  let videoRef = React.useRef(Js.Nullable.null);

  React.useEffect2(
    () => {
      // let contraints = Navigator.MediaDevices.Constraints.make();
      if (state.video.on || state.audio.on) {
        Navigator.MediaDevices.getUserMedia({
          video: state.video.on,
          audio: state.audio.on,
        })
        ->Promise.get(mediaStream =>
            setVideo(~video=videoRef.current, ~mediaStream)
          )
        ->ignore;
      };

      None;
    },
    (state.audio.on, state.video.on),
  );

  <div className="flex flex-col h-screen w-full relative">
    <div className="shadow-lg m-24 flex items-center p-24">
      <div className="w-2/3">
        <div
          className="shadow-xl rounded-xl h-96 overflow-hidden border border-gray">
          <video ref={ReactDOM.Ref.domRef(videoRef)} />
        </div>
      </div>
      <div className="w-1/3 flex flex-col items-center justify-center">
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Video size="36" /> </div>
          <Switch
            checked={state.video.on}
            loading={state.video.loading}
            onChange={value =>
              ToggleVideo({loading: value, on: value})->dispatch
            }
          />
        </div>
        <div className="text-gray-400 flex items-center py-4">
          <div className="mr-8"> <Icons.Mic size="36" /> </div>
          <Switch
            loading={state.audio.loading}
            checked={state.audio.on}
            onChange={value =>
              ToggleAudio({loading: value, on: value})->dispatch
            }
          />
        </div>
      </div>
    </div>
  </div>;
};
