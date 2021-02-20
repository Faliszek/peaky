

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import Peerjs from "peerjs";
import * as Peer$Peaky from "./Peer.bs.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Router$Peaky from "./Router.bs.js";
import * as WebRTC$Peaky from "./WebRTC.bs.js";
import * as ReactFeather from "react-feather";
import * as CopyLink$Peaky from "./components/CopyLink.bs.js";
import * as Patient_Add_Event$Peaky from "./Patient_Add_Event.bs.js";

function useVideoCall(isPatient, doctorPeerId, patientPeerId, localStream, setRemote, peer) {
  React.useEffect((function () {
          if (isPatient) {
            peer.call(doctorPeerId, localStream);
            peer.on("error", (function (_err) {
                    peer.call(doctorPeerId, localStream);
                    
                  }));
            peer.on("call", (function (call) {
                    call.answer(localStream);
                    call.on("stream", (function (remote) {
                            Belt_Option.map((remote == null) ? undefined : Caml_option.some(remote), (function (r) {
                                    return Curry._1(setRemote, (function (param) {
                                                  return Caml_option.some(r);
                                                }));
                                  }));
                            
                          }));
                    
                  }));
          } else {
            peer.call(patientPeerId, localStream);
            peer.on("error", (function (_err) {
                    peer.call(patientPeerId, localStream);
                    
                  }));
            peer.on("call", (function (call) {
                    call.answer(localStream);
                    call.on("stream", (function (remote) {
                            Belt_Option.map((remote == null) ? undefined : Caml_option.some(remote), (function (r) {
                                    return Curry._1(setRemote, (function (param) {
                                                  return Caml_option.some(r);
                                                }));
                                  }));
                            
                          }));
                    
                  }));
          }
          
        }), []);
  
}

var close = (function() {
    window.close();
  });

function Call_View_Meeting(Props) {
  var media = Props.media;
  var setMedia = Props.setMedia;
  var callId = Props.callId;
  var patientId = Props.patientId;
  var doctorId = Props.doctorId;
  var localStream = Props.localStream;
  var isPatient = Props.isPatient;
  var doctorPeerId = doctorId.replace("-", "");
  var patientPeerId = patientId.replace("-", "");
  var match = React.useState(function () {
        
      });
  var remote = match[0];
  var peerId = isPatient ? patientPeerId : doctorPeerId;
  var peer = React.useRef(new Peerjs(peerId, {
            host: "localhost",
            path: "/calls",
            port: "9000",
            debug: 1,
            config: {
              iceServers: Peer$Peaky.iceServers
            },
            pingInterval: 5000
          }));
  var match$1 = React.useState(function () {
        return false;
      });
  var setEnded = match$1[1];
  useVideoCall(isPatient, doctorPeerId, patientPeerId, localStream, match[1], peer.current);
  var localClassName = Belt_Option.isSome(remote) ? "w-64 h-auto absolute bottom-12 left-4 shadow-xl border-2 border-gray rounded-xl" : "";
  var remoteClassName = Belt_Option.isSome(remote) ? "w-full h-full" : "";
  if (isPatient && match$1[0]) {
    return React.createElement("div", {
                className: "bg-black w-screen h-screen flex items-center justify-center"
              }, React.createElement("div", {
                    className: "text-3xl text-white"
                  }, React.createElement(Text$Peaky.make, {
                        children: "Spotkanie zostało zakończone"
                      })));
  }
  var tmp;
  if (remote !== undefined) {
    var remote$1 = Caml_option.valFromOption(remote);
    tmp = React.createElement("video", {
          ref: (function (el) {
              return WebRTC$Peaky.setVideo(el, remote$1, true);
            }),
          className: Cn.$plus("transform rounded-xl border-2 border-gray bg-black", remoteClassName),
          style: {
            transform: "scale(-1, 1)"
          }
        });
  } else {
    tmp = null;
  }
  return React.createElement("div", {
              className: "flex items-center justify-center h-screen"
            }, tmp, React.createElement("video", {
                  ref: (function (el) {
                      return WebRTC$Peaky.setVideo(el, localStream, media.video);
                    }),
                  className: Cn.$plus("transform rounded-xl", localClassName),
                  style: {
                    transform: "scale(-1, 1)"
                  }
                }), Belt_Option.isNone(remote) ? React.createElement("div", {
                    className: "bg-black opacity-50 text-3xl text-white w-full h-full flex items-center justify-center absolute top-0 left-0"
                  }, React.createElement(Text$Peaky.make, {
                        children: "Twój rozmówca jeszcze nie dołączył do rozmowy"
                      })) : null, React.createElement("div", {
                  className: "fixed bottom-24 flex  gap-4"
                }, React.createElement(Button$Peaky.Round.make, {
                      icon: media.audio ? React.createElement(ReactFeather.Mic, {
                              size: "36"
                            }) : React.createElement(ReactFeather.MicOff, {
                              size: "36"
                            }),
                      onClick: (function (param) {
                          return Curry._1(setMedia, {
                                      TAG: /* SetAudio */0,
                                      _0: !media.audio
                                    });
                        }),
                      className: "bg-white  text-gray-600 hover:bg-gray-100"
                    }), React.createElement(Button$Peaky.Round.make, {
                      icon: media.video ? React.createElement(ReactFeather.Video, {
                              size: "36"
                            }) : React.createElement(ReactFeather.VideoOff, {
                              size: "36"
                            }),
                      onClick: (function (param) {
                          return Curry._1(setMedia, {
                                      TAG: /* SetVideo */1,
                                      _0: !media.video
                                    });
                        }),
                      className: "bg-white text-gray-600  hover:bg-gray-100"
                    }), React.createElement(Button$Peaky.Round.make, {
                      icon: React.createElement(ReactFeather.Phone, {
                            size: "36"
                          }),
                      onClick: (function (param) {
                          if (isPatient) {
                            return Curry._1(setEnded, (function (param) {
                                          return true;
                                        }));
                          } else {
                            return Router$Peaky.push(/* Calendar */0);
                          }
                        }),
                      className: "bg-red-400 text-white  hover:bg-red-300"
                    })), isPatient ? null : React.createElement(React.Fragment, undefined, React.createElement(Patient_Add_Event$Peaky.make, {
                        patientId: isPatient ? undefined : patientId
                      }), React.createElement(CopyLink$Peaky.make, {
                        link: "http://localhost:8080/calls/" + callId + "/" + doctorId + "/" + patientId
                      })));
}

var make = Call_View_Meeting;

export {
  useVideoCall ,
  close ,
  make ,
  
}
/* react Not a pure module */
