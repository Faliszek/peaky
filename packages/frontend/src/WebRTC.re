let setVideo = [%raw
  {|
   function initVideo(video, mediaStream) {
       video.srcObject = mediaStream
       if(mediaStream) {
        video.play()
       } else {
        video.pause()
       }
  }
  |}
];

type mediaState =
  | Off
  | Awaits
  | On;

type state = {
  video: mediaState,
  audio: mediaState,
};

type action =
  | ToggleVideo(bool)
  | ToggleAudio(bool);

let initialState = {video: Off, audio: Off};

let toMediaState = (~state, ~enabled) =>
  switch (state, enabled) {
  | (Off, true) => Awaits
  | (Awaits, true) => On
  | (_, false) => Off
  | _ => state
  };

let reducer = (state, action) =>
  switch (action) {
  | ToggleVideo(enabled) => {
      ...state,
      video: toMediaState(~state=state.video, ~enabled),
    }

  | ToggleAudio(enabled) => {
      ...state,
      audio: toMediaState(~state=state.audio, ~enabled),
    }
  };

module MediaDevices = {
  type mediaStream;

  module Constraints = {
    type t = {
      audio: option(bool),
      video: option(bool),
    };

    [@bs.obj] external make: (~audio: bool=?, ~video: bool=?, unit) => t;
  };

  module Video = {
    type mediaStream;
  };

  [@bs.scope ("window", "navigator", "mediaDevices")] [@bs.val]
  external getUserMedia: Constraints.t => Js.Promise.t(mediaStream) =
    "getUserMedia";
};

let getUserWebCamStream = (~onSuccess) => {
  MediaDevices.getUserMedia(MediaDevices.Constraints.make(~video=true, ()))
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.Js.get(res => {
      switch (res) {
      | Ok(mediaStream) => onSuccess(mediaStream)
      | Error(err) => Js.log(err)
      }
    });
};

let getUserMicStream = (~onSuccess) => {
  MediaDevices.getUserMedia(MediaDevices.Constraints.make(~audio=true, ()))
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.Js.get(res => {
      switch (res) {
      | Ok(mediaStream) => onSuccess(mediaStream)
      | Error(err) => Js.log(err)
      }
    });
};

let use = (~videoElement: React.ref(Js.Nullable.t('a))) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let onAudio = () => {
    switch (state.audio) {
    | Awaits => getUserMicStream(~onSuccess=_ => dispatch(ToggleAudio(true)))
    | Off => ()
    | _ => Js.log("")
    };
    None;
  };

  React.useEffect1(
    () => {
      let videoEl = Js.Nullable.toOption(videoElement.current);

      switch (videoEl, state.video) {
      | (Some(video), Awaits) =>
        getUserWebCamStream(~onSuccess=mediaStream => {
          Js.log("Success");
          setVideo(~video, ~mediaStream)->ignore;
          dispatch(ToggleVideo(true));
        })

      | (Some(video), Off) => setVideo(~video, ~mediaStream=None)
      | _ => Js.log("No video element")
      };
      None;
    },
    [|state.video|],
  );
  React.useEffect1(onAudio, [|state.audio|]);

  (state, dispatch);
};
