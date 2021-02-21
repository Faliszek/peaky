

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Switch$Peaky from "./components/Switch.bs.js";
import * as WebRTC$Peaky from "./WebRTC.bs.js";
import * as ReactFeather from "react-feather";

function Call_View_Preroom(Props) {
  var stream = Props.stream;
  var media = Props.media;
  var setMedia = Props.setMedia;
  var onJoin = Props.onJoin;
  var loading = Props.loading;
  return React.createElement("div", {
              className: "w-full h-screen flex"
            }, React.createElement("div", {
                  className: "shadow-lg m-24 flex  flex-wrap  items-center px-24 py-8 w-full"
                }, React.createElement("div", {
                      className: "w-2/3 flex h-2/3 items-center justify-center"
                    }, React.createElement("div", {
                          className: "shadow-xl rounded-xl  overflow-hidden border border-gray h-full w-full flex items-center justify-center bg-black "
                        }, media.video ? React.createElement("video", {
                                ref: (function (el) {
                                    return WebRTC$Peaky.setVideo(el, stream, media.video);
                                  }),
                                className: "transform w-full",
                                style: {
                                  transform: "scale(-1, 1)"
                                }
                              }) : React.createElement("div", {
                                className: "bg-black w-full h-full flex items-center justify-center"
                              }, React.createElement("div", {
                                    className: "text-3xl text-white"
                                  }, React.createElement(Text$Peaky.make, {
                                        children: "Twoja kamera jest wyłączona"
                                      }))))), React.createElement("div", {
                      className: "w-1/3 flex flex-col items-center justify-center"
                    }, React.createElement("div", {
                          className: "text-gray-400 flex items-center py-4"
                        }, React.createElement("div", {
                              className: "mr-8"
                            }, React.createElement(ReactFeather.Video, {
                                  size: "36"
                                })), React.createElement(Switch$Peaky.make, {
                              checked: media.video,
                              onChange: (function (value) {
                                  return Curry._1(setMedia, {
                                              TAG: /* SetVideo */1,
                                              _0: value
                                            });
                                })
                            })), React.createElement("div", {
                          className: "text-gray-400 flex items-center py-4"
                        }, React.createElement("div", {
                              className: "mr-8"
                            }, React.createElement(ReactFeather.Mic, {
                                  size: "36"
                                })), React.createElement(Switch$Peaky.make, {
                              checked: media.audio,
                              onChange: (function (value) {
                                  return Curry._1(setMedia, {
                                              TAG: /* SetAudio */0,
                                              _0: value
                                            });
                                })
                            }))), React.createElement("div", {
                      className: "w-full  flex justify-center"
                    }, React.createElement(Button$Peaky.CTA.make, {
                          loading: loading,
                          children: React.createElement(Text$Peaky.make, {
                                children: "Dołącz do spotkania"
                              }),
                          onClick: (function (param) {
                              return Curry._1(onJoin, undefined);
                            })
                        }))));
}

var make = Call_View_Preroom;

export {
  make ,
  
}
/* react Not a pure module */
