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

module MediaTrack = {
  type t;
};

module MediaStream = {
  type t;

  [@bs.send] external getVideoTracks: (t, unit) => 't = "getVideoTracks";
  [@bs.send] external getAudioTracks: (t, unit) => 't = "getAudioTracks";
  [@bs.send] external addTrack: (t, MediaTrack.t) => 't = "addTrack";
  [@bs.send] external removeTrack: (t, MediaTrack.t) => 't = "removeTrack";
};
type state = {
  video: mediaState,
  audio: mediaState,
  mediaStream: option(MediaStream.t),
};

type action =
  | ToggleVideo(bool)
  | ToggleAudio(bool);

let initialState = {video: Off, audio: Off, mediaStream: None};

let toMediaState = (~state, ~enabled) =>
  switch (state, enabled) {
  | (Off, true) => Awaits
  | (Awaits, true) => On
  | (_, false) => Off
  | _ => state
  };

let toBool = t =>
  switch (t) {
  | On => true
  | _ => false
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
  module Constraints = {
    type t = {
      audio: bool,
      video: bool,
    };

    [@bs.obj] external make: (~audio: bool=?, ~video: bool=?, unit) => t;
  };

  module Video = {
    type mediaStream;
  };

  [@bs.scope ("window", "navigator", "mediaDevices")] [@bs.val]
  external getUserMedia: Constraints.t => Js.Promise.t(MediaStream.t) =
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

      switch (videoEl, state.video, state.mediaStream) {
      | (Some(video), Awaits, None) =>
        getUserWebCamStream(~onSuccess=mediaStream => {
          setVideo(~video, ~mediaStream)->ignore;
          dispatch(ToggleVideo(true));
        })
      | (Some(video), Off, _) => setVideo(~video, ~mediaStream=None)
      | _ => Js.log("No video element")
      };
      None;
    },
    [|state.video|],
  );
  React.useEffect1(onAudio, [|state.audio|]);

  switch (state.mediaStream) {
  | Some(mediaStream) =>
    Js.log3(
      "Success",
      mediaStream->MediaStream.getAudioTracks(),
      mediaStream->MediaStream.getVideoTracks(),
    )

  | None => Js.log("No media stream provided")
  };

  (state, dispatch);
};

module UserMedia = {
  //   open WebRTC;
  //   module Provider = {
  //     [@bs.module "@vardius/react-user-media"] [@react.component]
  //     external make:
  //       (~constraints: MediaDevices.Constraints.t, ~children: React.element) =>
  //       React.element =
  //       "UserMediaProvider";
  //   };

  //   type hook = {stream: MediaStream.t};
  //   [@bs.module "@vardius/react-user-media"]

  //   external use: MediaDevices.Constraints.t => hook = "useUserMedia";
  type hook = {stream: Js.Nullable.t(MediaStream.t)};
  let use = [%raw
    {|

function useUserMedia(constraints) {
  const [stream, setStream] = React.useState(null);
  const [error, setError] = React.useState(null);

  React.useEffect(() => {
    if (stream) return;

    let didCancel = false;

    const getUserMedia = async () => {
      try {
        const stream = await navigator.mediaDevices.getUserMedia(constraints);
        if (!didCancel) {
          setStream(stream);
        }
      } catch (err) {
        if (!didCancel) {
          setError(err);
        }
      }
    }

    const cancel = () => {
      didCancel = true;

      if (!stream) return;

      if (stream.getVideoTracks) {
        stream.getVideoTracks().map(track => track.stop());
      }

      if (stream.getAudioTracks) {
        stream.getAudioTracks().map(track => track.stop());
      }

      if (stream.stop) {
        stream.stop();
      }
    }

    if(constraints.video || constraints.audio) {
    getUserMedia();

    }

    return cancel;
  }, [constraints, stream, error]);

  return {
    stream,
    error,
  };
}
    |}
  ];
};
