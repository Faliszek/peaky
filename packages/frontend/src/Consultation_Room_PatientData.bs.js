

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "@rescript/std/lib/es6/belt_Array.js";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as NoData$Peaky from "./components/NoData.bs.js";
import * as UseDebounce from "use-debounce";
import * as ReactFeather from "react-feather";
import * as ReactSketchCanvas from "react-sketch-canvas";
import * as Patient_Details_View$Peaky from "./Patient_Details_View.bs.js";

var exportPath = (function(canvas, cb) {
  if(canvas) {
    canvas.exportSvg().then(data => cb(data))
  }
});

function Consultation_Room_PatientData(Props) {
  var patientId = Props.patientId;
  var callerId = Props.callerId;
  var myId = Props.myId;
  var color = Props.color;
  var onChange = Props.onChange;
  var saveElCanvas = Props.saveElCanvas;
  var canvases = Props.data;
  var match = React.useState(function () {
        return "400";
      });
  var setWidth = match[1];
  var match$1 = React.useState(function () {
        return "400";
      });
  var setHeight = match$1[1];
  var amICaller = myId === callerId;
  var canvasEl = React.useRef(null);
  var match$2 = React.useState(function () {
        return [];
      });
  var setData = match$2[1];
  var waitForData = UseDebounce.useDebounce(match$2[0], 200);
  var debouncedData = Belt_Array.get(waitForData, 0);
  React.useEffect((function () {
          exportPath(canvasEl.current, onChange);
          Curry._1(saveElCanvas, canvasEl.current);
          
        }), [debouncedData]);
  console.log(canvases);
  var tmp;
  var exit = 0;
  if (amICaller && patientId === undefined) {
    tmp = React.createElement(NoData$Peaky.make, {
          title: "Wybierz pacjenta",
          text: "Dane wrażliwe nie zostaną wyświetlane dla innych uczestników",
          icon: React.createElement(ReactFeather.AlertCircle, {
                size: "64"
              })
        });
  } else {
    exit = 1;
  }
  if (exit === 1) {
    tmp = patientId !== undefined ? React.createElement(Patient_Details_View$Peaky.make, {
            id: patientId,
            callMode: true
          }) : React.createElement(NoData$Peaky.make, {
            title: "Prowadzący nie wybrał jeszcze pacjenta",
            text: "Po wybraniu pacjenta przez prowadzącego, tutaj pojawi się widok przebiegu choroby",
            icon: React.createElement(ReactFeather.AlertCircle, {
                  size: "64"
                })
          });
  }
  return React.createElement("div", {
              className: "relative"
            }, React.createElement("div", {
                  ref: (function (el) {
                      Belt_Option.map((el == null) ? undefined : Caml_option.some(el), (function (el) {
                              return setTimeout((function (param) {
                                            Curry._1(setWidth, (function (param) {
                                                    return el.offsetWidth.toString() + "px";
                                                  }));
                                            return Curry._1(setHeight, (function (param) {
                                                          return el.offsetHeight.toString() + "px";
                                                        }));
                                          }), 100);
                            }));
                      
                    })
                }, tmp), Belt_Array.map(canvases, (function (x) {
                    if (x.id === myId) {
                      return null;
                    } else {
                      return React.createElement("div", {
                                  key: x.id,
                                  className: "absolute w-full h-full top-0 left-0"
                                }, React.createElement("div", {
                                      dangerouslySetInnerHTML: {
                                        __html: x.svg
                                      }
                                    }));
                    }
                  })), React.createElement("div", {
                  className: "absolute w-full h-full top-0 left-0 shadow-xl"
                }, React.createElement(ReactSketchCanvas.ReactSketchCanvas, {
                      width: match[0],
                      height: match$1[0],
                      background: "transparent",
                      strokeColor: color,
                      onUpdate: (function (data) {
                          return Curry._1(setData, (function (param) {
                                        return data;
                                      }));
                        }),
                      ref: canvasEl,
                      withTimestamp: true,
                      style: {
                        border: "none"
                      }
                    })));
}

var make = Consultation_Room_PatientData;

export {
  exportPath ,
  make ,
  
}
/* react Not a pure module */
