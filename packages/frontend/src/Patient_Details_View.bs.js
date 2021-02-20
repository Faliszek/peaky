

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as DateFns from "date-fns";
import * as ReactVis from "react-vis";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Page$Peaky from "./components/Page.bs.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_format from "bs-platform/lib/es6/caml_format.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Input$Peaky from "./components/Input.bs.js";
import * as Modal$Peaky from "./components/Modal.bs.js";
import * as Avatar$Peaky from "./components/Avatar.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as NoData$Peaky from "./components/NoData.bs.js";
import * as Request$Peaky from "./Request.bs.js";
import * as Spinner$Peaky from "./components/Spinner.bs.js";
import * as ReactFeather from "react-feather";
import * as Color_Picker$Peaky from "./Color_Picker.bs.js";
import * as Patient_Block$Peaky from "./Patient_Block.bs.js";
import * as Patient_Query$Peaky from "./Patient_Query.bs.js";
import * as Calendar_Query$Peaky from "./Calendar_Query.bs.js";
import * as Symptoms_Table$Peaky from "./Symptoms_Table.bs.js";
import * as Visit_Mutation$Peaky from "./Visit_Mutation.bs.js";
import * as Symptom_Mutation$Peaky from "./Symptom_Mutation.bs.js";
import * as Calendar_AddVisit$Peaky from "./Calendar_AddVisit.bs.js";
import * as Patient_Add_Event$Peaky from "./Patient_Add_Event.bs.js";

function Patient_Details_View$Section(Props) {
  var title = Props.title;
  var icon = Props.icon;
  var children = Props.children;
  var button = Props.button;
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  className: "flex items-center justify-between text-2xl text-gray-700 mb-8 mt-12 pb-4"
                }, React.createElement("div", {
                      className: "flex items-center"
                    }, React.createElement("div", {
                          className: "p-2 cursor-pointer rounded-lg  mr-4 border-2 border-green-50 bg-green-50"
                        }, React.createElement("span", {
                              className: "text-green-400"
                            }, icon)), React.createElement("span", {
                          className: "text-gray-500"
                        }, React.createElement(Text$Peaky.make, {
                              children: title
                            }))), button !== undefined ? Caml_option.valFromOption(button) : null), children);
}

var Section = {
  make: Patient_Details_View$Section
};

function Patient_Details_View$Symptom_Add(Props) {
  var patientId = Props.patientId;
  var visible = Props.visible;
  var onClose = Props.onClose;
  var callMode = Props.callMode;
  var match = React.useState(function () {
        return "";
      });
  var setSymptomName = match[1];
  var symptomName = match[0];
  var match$1 = React.useState(function () {
        return "";
      });
  var setCircumstances = match$1[1];
  var circumstances = match$1[0];
  var match$2 = React.useState(function () {
        return "";
      });
  var setDate = match$2[1];
  var date = match$2[0];
  var match$3 = React.useState(function () {
        return "";
      });
  var setOccurences = match$3[1];
  var occurences = match$3[0];
  var match$4 = React.useState(function () {
        return "";
      });
  var setDescription = match$4[1];
  var description = match$4[0];
  var match$5 = React.useState(function () {
        return "";
      });
  var setCausedBy = match$5[1];
  var causedBy = match$5[0];
  var match$6 = React.useState(function () {
        return "";
      });
  var setColor = match$6[1];
  var color = match$6[0];
  var match$7 = React.useState(function () {
        return "";
      });
  var setNotes = match$7[1];
  var notes = match$7[0];
  var match$8 = Curry.app(Symptom_Mutation$Peaky.Mutation.use, [
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
        [Curry._3(Patient_Query$Peaky.Query.refetchQueryDescription, undefined, undefined, {
                id: patientId
              })],
        undefined,
        undefined
      ]);
  if (callMode) {
    return null;
  }
  var createSymptom = match$8[0];
  return React.createElement(Modal$Peaky.make, {
              visible: visible,
              onVisibleChange: (function (param) {
                  return Curry._1(onClose, undefined);
                }),
              children: null,
              onOk: (function (param) {
                  return Request$Peaky.onFinish(Curry._8(createSymptom, undefined, undefined, undefined, undefined, undefined, undefined, undefined, {
                                  patientId: patientId,
                                  name: symptomName,
                                  date: date,
                                  circumstances: circumstances,
                                  description: description,
                                  occurences: occurences,
                                  causedBy: causedBy,
                                  notes: notes,
                                  color: color
                                }), (function (param) {
                                return Curry._1(onClose, undefined);
                              }), (function (prim) {
                                console.log(prim);
                                
                              }));
                }),
              loading: match$8[1].loading
            }, React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: symptomName,
                        onChange: (function (v) {
                            return Curry._1(setSymptomName, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Nazwa"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: circumstances,
                        onChange: (function (v) {
                            return Curry._1(setCircumstances, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Okoliczności pojawienia się"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: date,
                        onChange: (function (v) {
                            return Curry._1(setDate, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Data pierwszego wystąpienia"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: occurences,
                        onChange: (function (v) {
                            return Curry._1(setOccurences, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Częstotliwość występowania"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: description,
                        onChange: (function (v) {
                            return Curry._1(setDescription, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Opis"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: causedBy,
                        onChange: (function (v) {
                            return Curry._1(setCausedBy, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Spowodowany przez"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.Textarea.make, {
                        placeholder: "Dodatkowe informacje",
                        value: notes,
                        onChange: (function (v) {
                            return Curry._1(setNotes, (function (param) {
                                          return v;
                                        }));
                          })
                      })
                }), React.createElement(Color_Picker$Peaky.make, {
                  value: color,
                  onChange: (function (v) {
                      return Curry._1(setColor, (function (param) {
                                    return v;
                                  }));
                    })
                }));
}

var Symptom_Add = {
  make: Patient_Details_View$Symptom_Add
};

function Patient_Details_View$Legend(Props) {
  var title = Props.title;
  var color = Props.color;
  return React.createElement("div", {
              className: "flex justify-center items-center flex-col w-1/6"
            }, React.createElement("div", {
                  style: {
                    backgroundColor: color,
                    height: "3px",
                    width: "100%",
                    borderRadius: "10px"
                  }
                }), React.createElement("div", {
                  className: "text-sm text-gray-800 mt-2"
                }, React.createElement(Text$Peaky.make, {
                      children: title
                    })));
}

var Legend = {
  make: Patient_Details_View$Legend
};

function Patient_Details_View(Props) {
  var id = Props.id;
  var callModeOpt = Props.callMode;
  var callMode = callModeOpt !== undefined ? callModeOpt : false;
  var match = React.useState(function () {
        return false;
      });
  var setVisible = match[1];
  var query = Curry.app(Calendar_Query$Peaky.Query.use, [
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
  var patientQuery = Curry.app(Patient_Query$Peaky.Query.use, [
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
        {
          id: id
        }
      ]);
  var match$1 = Curry.app(Visit_Mutation$Peaky.Mutation.use, [
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
        [Curry._3(Calendar_Query$Peaky.Query.refetchQueryDescription, undefined, undefined, undefined)],
        undefined,
        undefined
      ]);
  var createVisit = match$1[0];
  var name = callMode ? "-" : Belt_Option.getWithDefault(Belt_Option.map(patientQuery.data, (function (param) {
                var patient = param.patient;
                return patient.firstName + (" " + patient.lastName);
              })), "");
  var match$2 = React.useState(function () {
        
      });
  var setWidth = match$2[1];
  var match$3 = React.useState(function () {
        return false;
      });
  var setModalVisible = match$3[1];
  var match$4 = React.useState(function () {
        return false;
      });
  var setCreatorVisible = match$4[1];
  var match$5 = patientQuery.data;
  var tmp;
  if (patientQuery.loading) {
    tmp = React.createElement(Spinner$Peaky.make, {});
  } else if (match$5 !== undefined) {
    var patient = match$5.patient;
    tmp = React.createElement("div", {
          className: "flex items-center"
        }, React.createElement("div", {
              className: "flex flex-1 items-center ml-4"
            }, React.createElement(Avatar$Peaky.make, {
                  firstName: callMode ? "X" : patient.firstName,
                  lastName: callMode ? "X" : patient.lastName,
                  size: "big",
                  color: patient.color
                }), React.createElement(Patient_Block$Peaky.Info.make, {
                  name: callMode ? "" : name,
                  phoneNumber: callMode ? "" : patient.phoneNumber,
                  disease: patient.disease,
                  lastVisit: patient.lastVisit
                })), callMode ? null : React.createElement("div", {
                className: "ml-16 flex  flex-1 flex-col items-start justify-start"
              }, React.createElement(Button$Peaky.CTA.make, {
                    children: React.createElement(Text$Peaky.make, {
                          children: "Dodaj wizytę"
                        }),
                    icon: React.createElement(ReactFeather.Plus, {
                          className: "mr-4"
                        }),
                    type_: "ghost",
                    onClick: (function (param) {
                        return Curry._1(setVisible, (function (param) {
                                      return true;
                                    }));
                      })
                  }), React.createElement("div", {
                    className: "h-4"
                  }), React.createElement(Button$Peaky.CTA.make, {
                    children: React.createElement(Text$Peaky.make, {
                          children: "Aktualizuj przebieg leczenia"
                        }),
                    icon: React.createElement(ReactFeather.Thermometer, {
                          className: "mr-4"
                        }),
                    onClick: (function (param) {
                        return Curry._1(setCreatorVisible, (function (param) {
                                      return true;
                                    }));
                      })
                  })));
  } else {
    tmp = null;
  }
  var match$6 = patientQuery.data;
  var tmp$1;
  if (patientQuery.loading) {
    tmp$1 = React.createElement(Spinner$Peaky.make, {});
  } else if (match$6 !== undefined) {
    var patientEvents = match$6.patientEvents;
    var symptoms = match$6.symptoms;
    var feelings = Belt_Array.map(match$6.feelings, (function (f) {
            return {
                    x: f.timestamp,
                    y: Caml_format.caml_float_of_string(f.value)
                  };
          }));
    var symptomIds = Belt_Array.reduce(patientEvents, [], (function (acc, param) {
            var symptompId = param.symptompId;
            if (Belt_Option.isSome(Belt_Array.get(Belt_Array.keep(acc, (function (id) {
                              return id === symptompId;
                            })), 0))) {
              return acc;
            } else {
              return Belt_Array.concat(acc, [symptompId]);
            }
          }));
    var symptomsData = Belt_Array.reduce(symptomIds, [], (function (acc, id) {
            return Belt_Array.concat(acc, [{
                          id: id,
                          color: Belt_Option.getWithDefault(Belt_Option.map(Belt_Array.get(Belt_Array.keep(symptoms, (function (s) {
                                              return s.id === id;
                                            })), 0), (function (s) {
                                      return s.color;
                                    })), ""),
                          data: Belt_Array.map(Belt_Array.keep(patientEvents, (function (e) {
                                      return e.symptompId === id;
                                    })), (function (e) {
                                  return {
                                          x: e.timestamp,
                                          y: e.feeling
                                        };
                                }))
                        }]);
          }));
    tmp$1 = React.createElement("div", undefined, React.createElement("div", {
              ref: (function (el) {
                  return Curry._1(setWidth, (function (param) {
                                return Belt_Option.map((el == null) ? undefined : Caml_option.some(el), (function (el) {
                                              return el.offsetWidth;
                                            }));
                              }));
                }),
              className: "flex items-center gap-8"
            }, React.createElement(ReactVis.XYPlot, {
                  children: null,
                  width: Belt_Option.getWithDefault(match$2[0], 600.0),
                  height: 300.0
                }, React.createElement(ReactVis.HorizontalGridLines, {
                      style: {
                        stroke: "#E2E8F0"
                      }
                    }), React.createElement(ReactVis.XAxis, {
                      attr: "x",
                      attrAxis: "y",
                      orientation: "bottom",
                      tickFormat: (function (v) {
                          return DateFns.format(v, "dd.MM.yy");
                        }),
                      tickTotal: 8
                    }), React.createElement(ReactVis.YAxis, {
                      attr: "y",
                      attrAxis: "x",
                      orientation: "left"
                    }), React.createElement(ReactVis.LineSeries, {
                      data: feelings,
                      opacity: 1.0,
                      strokeStyle: "solid",
                      curve: "curveMonotoneX",
                      style: {
                        fill: "none",
                        stroke: "green",
                        strokeWidth: "5px"
                      }
                    }), Belt_Array.map(symptomsData, (function (s) {
                        return React.createElement(ReactVis.LineSeries, {
                                    data: s.data,
                                    opacity: 1.0,
                                    strokeStyle: "solid",
                                    curve: "curveMonotoneX",
                                    style: {
                                      fill: "none",
                                      stroke: s.color,
                                      strokeWidth: "5px"
                                    },
                                    key: s.id
                                  });
                      })))), React.createElement("div", {
              className: "flex gap-10 px-8 pt-16 pb-8 justify-center"
            }, React.createElement(Patient_Details_View$Legend, {
                  title: "Ogólne samopoczucie",
                  color: "green",
                  key: "feeling"
                }), Belt_Array.map(symptoms, (function (s) {
                    return React.createElement(Patient_Details_View$Legend, {
                                title: s.name,
                                color: s.color,
                                key: s.id
                              });
                  }))));
  } else {
    tmp$1 = null;
  }
  var match$7 = patientQuery.data;
  var tmp$2;
  if (patientQuery.loading) {
    tmp$2 = React.createElement(Spinner$Peaky.make, {});
  } else if (match$7 !== undefined) {
    var symptoms$1 = match$7.symptoms;
    tmp$2 = symptoms$1.length === 0 ? React.createElement(NoData$Peaky.make, {
            title: "Brak objawów",
            text: "Pacjent zdrowy"
          }) : React.createElement(React.Fragment, undefined, React.createElement(Symptoms_Table$Peaky.make, {
                symptoms: symptoms$1
              }));
  } else {
    tmp$2 = null;
  }
  var data = query.data;
  return React.createElement(Page$Peaky.make, {
              title: callMode ? "" : "Detale: " + name,
              children: null,
              hasBackButton: callMode ? false : true
            }, React.createElement(Page$Peaky.Block.make, {
                  children: tmp
                }), React.createElement(Patient_Details_View$Section, {
                  title: "Przebieg choroby",
                  icon: React.createElement(ReactFeather.BarChart, {}),
                  children: tmp$1
                }), React.createElement(Patient_Details_View$Section, {
                  title: "Symptomy",
                  icon: React.createElement(ReactFeather.Thermometer, {}),
                  children: null,
                  button: callMode ? null : React.createElement(Button$Peaky.CTA.make, {
                          children: React.createElement(Text$Peaky.make, {
                                children: "Dodaj symptom"
                              }),
                          onClick: (function (param) {
                              return Curry._1(setModalVisible, (function (param) {
                                            return true;
                                          }));
                            })
                        })
                }, React.createElement(Patient_Details_View$Symptom_Add, {
                      patientId: id,
                      visible: match$3[0],
                      onClose: (function (param) {
                          return Curry._1(setModalVisible, (function (param) {
                                        return false;
                                      }));
                        }),
                      callMode: callMode
                    }), tmp$2), data !== undefined ? React.createElement(Calendar_AddVisit$Peaky.make, {
                    patientId: id,
                    visible: match[0],
                    onClose: (function (param) {
                        return Curry._1(setVisible, (function (param) {
                                      return false;
                                    }));
                      }),
                    date: undefined,
                    patients: data.patients,
                    loading: match$1[1].loading,
                    onSubmit: (function (patientId, from_, to_, notes) {
                        return Request$Peaky.onFinish(Curry._8(createVisit, undefined, undefined, undefined, undefined, undefined, undefined, undefined, {
                                        patientId: patientId,
                                        from_: from_,
                                        to_: to_,
                                        notes: notes
                                      }), (function (param) {
                                      return Curry._1(setVisible, (function (param) {
                                                    return false;
                                                  }));
                                    }), (function (param) {
                                      
                                    }));
                      })
                  }) : null, match$4[0] ? React.createElement(Patient_Add_Event$Peaky.AddEvent.make, {
                    onClose: (function (param) {
                        return Curry._1(setCreatorVisible, (function (param) {
                                      return false;
                                    }));
                      }),
                    patientId: id
                  }) : null);
}

var make = Patient_Details_View;

export {
  Section ,
  Symptom_Add ,
  Legend ,
  make ,
  
}
/* react Not a pure module */
