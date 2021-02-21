

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as Auth$Peaky from "./Auth.bs.js";
import * as WebRTC$Peaky from "./WebRTC.bs.js";
import * as Request$Peaky from "./Request.bs.js";
import * as Call_View_Meeting$Peaky from "./Call_View_Meeting.bs.js";
import * as Call_View_Preroom$Peaky from "./Call_View_Preroom.bs.js";
import * as Call_CreateRoom_Mutation$Peaky from "./Call_CreateRoom_Mutation.bs.js";

function Call_View(Props) {
  var callId = Props.id;
  var patientId = Props.patientId;
  var doctorId = Props.doctorId;
  var isPatient = Props.isPatient;
  var match = WebRTC$Peaky.use(undefined);
  var setMedia = match[2];
  var media = match[1];
  var stream = match[0];
  var match$1 = Curry.app(Call_CreateRoom_Mutation$Peaky.Mutation.use, [
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined
      ]);
  var mutation = match$1[0];
  var match$2 = React.useState(function () {
        return /* Preroom */0;
      });
  var setView = match$2[1];
  var view = match$2[0];
  if (isPatient) {
    return React.createElement("div", {
                className: "flex flex-col h-screen w-full relative"
              }, view ? React.createElement(Call_View_Meeting$Peaky.make, {
                      media: media,
                      setMedia: setMedia,
                      callId: callId,
                      patientId: patientId,
                      doctorId: doctorId,
                      localStream: stream,
                      isPatient: isPatient
                    }) : React.createElement(Call_View_Preroom$Peaky.make, {
                      stream: stream,
                      media: media,
                      setMedia: setMedia,
                      onJoin: (function (param) {
                          return Curry._1(setView, (function (param) {
                                        return /* Meeting */1;
                                      }));
                        }),
                      loading: false
                    }));
  }
  var userId = Auth$Peaky.getUserId(undefined);
  return React.createElement("div", {
              className: "flex flex-col h-screen w-full relative"
            }, view ? React.createElement(Call_View_Meeting$Peaky.make, {
                    media: media,
                    setMedia: setMedia,
                    callId: callId,
                    patientId: patientId,
                    doctorId: doctorId,
                    localStream: stream,
                    isPatient: isPatient
                  }) : React.createElement(Call_View_Preroom$Peaky.make, {
                    stream: stream,
                    media: media,
                    setMedia: setMedia,
                    onJoin: (function (param) {
                        return Request$Peaky.onFinish(Curry._8(mutation, undefined, undefined, undefined, undefined, undefined, undefined, undefined, {
                                        patientId: patientId,
                                        doctorId: userId
                                      }), (function (param) {
                                      if (param.createRoom !== undefined) {
                                        return Curry._1(setView, (function (param) {
                                                      return /* Meeting */1;
                                                    }));
                                      }
                                      
                                    }), (function (param) {
                                      
                                    }));
                      }),
                    loading: match$1[1].loading
                  }));
}

var make = Call_View;

export {
  make ,
  
}
/* react Not a pure module */
