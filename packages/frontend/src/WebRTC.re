let setVideo = [%raw
  {|
   function initVideo(video, mediaStream, on) {
     if(video) {
       video.srcObject = mediaStream
       if(mediaStream && on) {
        video.play()
       } else {
        video.pause()
       }
     }
  }
  |}
];

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

type mediaOptions = {
  audio: bool,
  video: bool,
};

type action =
  | SetAudio(bool)
  | SetVideo(bool);

let initialState = {video: false, audio: false};

let reducer = (state, action) =>
  switch (action) {
  | SetAudio(audio) => {...state, audio}
  | SetVideo(video) => {...state, video}
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

module Media = {
  type t = {
    .
    "active": bool,
    "id": string,
  };
  module Track = {
    type t = {
      enabled: bool,
      muted: bool,
      kind: string,
      id: string,
      stop: [@bs.meth] (unit => unit),
    };

    [@bs.set] external setEnabled: (t, bool) => unit = "enabled";

    [@bs.set] external onMute: (t, t => unit) => unit = "onmute";

    [@bs.set] external onEnd: (t, t => unit) => unit = "onended";
  };

  type srcObject = {
    .
    "id": string,
    "getTracks": [@bs.meth] (unit => array(Track.t)),
    "removeTrack": [@bs.meth] (Track.t => unit),
  };

  type event = {. "stream": srcObject};

  type trackEvent = {
    .
    "streams": array(srcObject),
    "track": Track.t,
  };

  [@bs.val] [@bs.scope ("window", "navigator", "mediaDevices")]
  external getUserMedia: mediaOptions => Js.Promise.t(srcObject) =
    "getUserMedia";
};

let setTrack = (~kind, ~stream: Js.Nullable.t(Media.srcObject), ~enabled) => {
  let track =
    stream
    ->Js.Nullable.toOption
    ->Option.map(s => s##getTracks())
    ->Option.flatMap(tracks => tracks->Array.getBy(t => t.kind == kind));

  switch (track) {
  | Some(track) => track->Media.Track.setEnabled(enabled)
  | None => ()
  };
};

module UserMedia = {
  type hook = {stream: Js.Nullable.t(Media.srcObject)};
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

      if (stream.getVideoTracks && !constraints.video) {

        stream.getVideoTracks().map(track => track.stop());
      }

      if (stream.getAudioTracks && !constraints.audio) {
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

let contstraints = {audio: true, video: true};
let use = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let {stream}: UserMedia.hook = UserMedia.use(contstraints);

  // stream
  // ->Js.Nullable.toOption
  // ->Option.map(s => Js.log(s##getTracks()))
  // ->ignore;
  React.useEffect2(
    () => {
      setTrack(~kind="audio", ~stream, ~enabled=state.audio);
      None;
    },
    (state.audio, stream),
  );

  React.useEffect2(
    () => {
      setTrack(~kind="video", ~stream, ~enabled=state.video);
      None;
    },
    (state.video, stream),
  );

  (stream, state, dispatch);
};
