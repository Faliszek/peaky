

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as $$Promise from "reason-promise/src/js/promise.bs.js";
import * as Belt_Array from "@rescript/std/lib/es6/belt_Array.js";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";

var setVideo = (function initVideo(video, mediaStream, on) {
     if(video && !video.srcObject) {
       video.srcObject = mediaStream
       if(mediaStream && on) {
        video.play()
       } else {
        video.pause()
       }
     }
  });

var MediaTrack = {};

var $$MediaStream = {};

var initialState = {
  audio: false,
  video: false
};

function reducer(state, action) {
  if (action.TAG === /* SetAudio */0) {
    return {
            audio: action._0,
            video: state.video
          };
  } else {
    return {
            audio: state.audio,
            video: action._0
          };
  }
}

var Constraints = {};

var Video = {};

var $$MediaDevices = {
  Constraints: Constraints,
  Video: Video
};

function getUserWebCamStream(onSuccess) {
  return $$Promise.Js.get($$Promise.Js.toResult($$Promise.Js.fromBsPromise(window.navigator.mediaDevices.getUserMedia({
                          video: true
                        }))), (function (res) {
                if (res.TAG === /* Ok */0) {
                  return Curry._1(onSuccess, res._0);
                }
                console.log(res._0);
                
              }));
}

function getUserMicStream(onSuccess) {
  return $$Promise.Js.get($$Promise.Js.toResult($$Promise.Js.fromBsPromise(window.navigator.mediaDevices.getUserMedia({
                          audio: true
                        }))), (function (res) {
                if (res.TAG === /* Ok */0) {
                  return Curry._1(onSuccess, res._0);
                }
                console.log(res._0);
                
              }));
}

var Track = {};

var Media = {
  Track: Track
};

function setTrack(kind, stream, enabled) {
  var track = Belt_Option.flatMap(Belt_Option.map((stream == null) ? undefined : Caml_option.some(stream), (function (s) {
              return s.getTracks();
            })), (function (tracks) {
          return Belt_Array.getBy(tracks, (function (t) {
                        return t.kind === kind;
                      }));
        }));
  if (track !== undefined) {
    track.enabled = enabled;
    return ;
  }
  
}

var use = (function useUserMedia(constraints) {
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
});

var UserMedia = {
  use: use
};

var contstraints = {
  audio: true,
  video: true
};

function use$1(param) {
  var match = React.useReducer(reducer, initialState);
  var state = match[0];
  var match$1 = use(contstraints);
  var stream = match$1.stream;
  React.useEffect((function () {
          setTrack("audio", stream, state.audio);
          
        }), [
        state.audio,
        stream
      ]);
  React.useEffect((function () {
          setTrack("video", stream, state.video);
          
        }), [
        state.video,
        stream
      ]);
  return [
          stream,
          state,
          match[1]
        ];
}

export {
  setVideo ,
  MediaTrack ,
  $$MediaStream ,
  initialState ,
  reducer ,
  $$MediaDevices ,
  getUserWebCamStream ,
  getUserMicStream ,
  Media ,
  setTrack ,
  UserMedia ,
  contstraints ,
  use$1 as use,
  
}
/* react Not a pure module */
