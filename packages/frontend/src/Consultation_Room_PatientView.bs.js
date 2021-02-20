

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Select$Peaky from "./components/Select.bs.js";
import * as Spinner$Peaky from "./components/Spinner.bs.js";
import * as ReactFeather from "react-feather";
import * as Color_Picker$Peaky from "./Color_Picker.bs.js";
import * as Patient_List_Query$Peaky from "./Patient_List_Query.bs.js";
import * as Consultation_Room_PatientData$Peaky from "./Consultation_Room_PatientData.bs.js";

function toSelectOptions(patients) {
  return Belt_Array.map(patients, (function (p) {
                return {
                        value: p.id,
                        label: p.firstName + (" " + p.lastName)
                      };
              }));
}

var updateCanvas = (function(canvas, data) {
    if(data !== "") {
      canvas.loadPaths(data);
    }
  });

var clearCanvas = (function(canvas) {
    if(canvas) {
      canvas.clearCanvas();
      }
  });

function useSharedData(peer, userIds, myId, setPatientId, patientId, setData) {
  var incoming = React.useRef(undefined);
  var calls = React.useRef([]);
  var send = function (conn, value) {
    conn.send(value);
    
  };
  var onDataChange = React.useCallback((function (data) {
          var i = incoming.current;
          if (i !== undefined) {
            send(i, data);
          }
          Belt_Array.map(calls.current, (function (c) {
                  if (c !== undefined) {
                    return send(c, data);
                  }
                  
                }));
          
        }), [patientId]);
  React.useEffect((function () {
          var handleConnection = function (c) {
            if (c !== undefined) {
              c.on("open", (function (param) {
                      c.on("data", (function (data) {
                              Curry._1(setPatientId, (function (v) {
                                      if (Caml_obj.caml_equal(v, data.patientId)) {
                                        return v;
                                      } else {
                                        return data.patientId;
                                      }
                                    }));
                              if (data.updater !== myId) {
                                return Curry._1(setData, (function (param) {
                                              return data.canvas;
                                            }));
                              }
                              
                            }));
                      
                    }));
              return ;
            }
            
          };
          peer.on("connection", (function (conn) {
                  incoming.current = conn;
                  return handleConnection(incoming.current);
                }));
          calls.current = Belt_Array.map(userIds, (function (x) {
                  return peer.connect(x, {
                              serialization: "json"
                            });
                }));
          Belt_Array.map(calls.current, handleConnection);
          
        }), []);
  return onDataChange;
}

function initalData(myId, userIds) {
  return Belt_Array.map(Belt_Array.concat(userIds, [myId]), (function (u) {
                return {
                        id: u,
                        svg: ""
                      };
              }));
}

function Consultation_Room_PatientView(Props) {
  var callerId = Props.callerId;
  var myId = Props.myId;
  var userIds = Props.userIds;
  var peer = Props.peer;
  var query = Curry.app(Patient_List_Query$Peaky.Query.use, [
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
        undefined,
        undefined
      ]);
  var patient = Select$Peaky.use(undefined);
  var callerId$1 = "data" + callerId;
  var match = React.useState(function () {
        return "rgb(96, 165, 250)";
      });
  var setColor = match[1];
  var color = match[0];
  var match$1 = React.useState(function () {
        return false;
      });
  var setVisible = match$1[1];
  var match$2 = React.useState(function () {
        
      });
  var setPatientId = match$2[1];
  var patientId = match$2[0];
  var match$3 = React.useState(function () {
        return initalData(myId, userIds);
      });
  var data = match$3[0];
  var canvasEl = React.useRef(undefined);
  var onDataChange = useSharedData(peer, userIds, myId, setPatientId, patientId, match$3[1]);
  React.useEffect((function () {
          Curry._1(onDataChange, {
                patientId: patientId,
                canvas: initalData(myId, userIds),
                updater: myId
              });
          clearCanvas(canvasEl.current);
          
        }), [patientId]);
  var match$4 = query.data;
  return React.createElement("div", {
              className: "w-full h-screen flex items-center"
            }, query.loading ? React.createElement(Spinner$Peaky.make, {}) : (
                match$4 !== undefined ? React.createElement("div", {
                        className: "h-full py-8 px-4 w-full"
                      }, React.createElement("div", {
                            className: "w-full flex gap-8 justify-between shadow-lg sticky border-bottom border-gray-300 top-0 p-4 rounded-xl z-20 bg-white"
                          }, callerId$1 === myId ? React.createElement("div", {
                                  className: "flex gap-8 justify-between"
                                }, React.createElement(Select$Peaky.make, {
                                      value: patient.value,
                                      search: patient.search,
                                      onSearchChange: patient.setSearch,
                                      placeholder: "Wybierz pacjenta",
                                      icon: React.createElement(ReactFeather.User, {
                                            size: "20"
                                          }),
                                      visible: patient.visible,
                                      onVisibleChange: patient.setVisible,
                                      options: toSelectOptions(match$4.patients),
                                      onChange: patient.setValue
                                    }), React.createElement(Button$Peaky.CTA.make, {
                                      children: React.createElement(Text$Peaky.make, {
                                            children: "Wybierz"
                                          }),
                                      onClick: (function (param) {
                                          return Curry._1(setPatientId, (function (param) {
                                                        return Belt_Option.map(patient.value, (function (x) {
                                                                      return x.value;
                                                                    }));
                                                      }));
                                        })
                                    })) : null, React.createElement("div", {
                                className: "flex items-center"
                              }, 0 !== 0 ? React.createElement(Button$Peaky.CTA.make, {
                                      children: React.createElement(Text$Peaky.make, {
                                            children: "Cofnij"
                                          }),
                                      icon: React.createElement(ReactFeather.ArrowLeft, {
                                            className: "mr-2"
                                          })
                                    }) : null, React.createElement(Button$Peaky.Nav.make, {
                                    onClick: (function (param) {
                                        return Curry._1(setVisible, (function (v) {
                                                      return !v;
                                                    }));
                                      }),
                                    children: null,
                                    className: "relative"
                                  }, React.createElement("span", {
                                        style: {
                                          color: color
                                        }
                                      }, React.createElement(ReactFeather.Edit3, {})), match$1[0] ? React.createElement(Color_Picker$Peaky.make, {
                                          value: color,
                                          onChange: (function (v) {
                                              return Curry._1(setColor, (function (param) {
                                                            return v;
                                                          }));
                                            }),
                                          className: "w-48 absolute right-0 top-4 border border-gray-200 shadow-lg bg-white p-4 z-30"
                                        }) : null))), React.createElement(Consultation_Room_PatientData$Peaky.make, {
                            patientId: patientId,
                            callerId: callerId$1,
                            myId: myId,
                            color: color,
                            onChange: (function (svg) {
                                return Curry._1(onDataChange, {
                                            patientId: patientId,
                                            canvas: Belt_Array.map(data, (function (x) {
                                                    if (x.id === myId) {
                                                      return {
                                                              id: x.id,
                                                              svg: svg
                                                            };
                                                    } else {
                                                      return x;
                                                    }
                                                  })),
                                            updater: myId
                                          });
                              }),
                            saveElCanvas: (function (el) {
                                canvasEl.current = Caml_option.some(el);
                                
                              }),
                            data: data
                          })) : null
              ));
}

var make = Consultation_Room_PatientView;

export {
  toSelectOptions ,
  updateCanvas ,
  clearCanvas ,
  useSharedData ,
  initalData ,
  make ,
  
}
/* react Not a pure module */
