

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as DateFns from "date-fns";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Caml_format from "bs-platform/lib/es6/caml_format.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Input$Peaky from "./components/Input.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Select$Peaky from "./components/Select.bs.js";
import * as SideNav$Peaky from "./components/SideNav.bs.js";
import * as ReactFeather from "react-feather";

function toSelectOptions(patients) {
  return Belt_Array.map(patients, (function (p) {
                return {
                        value: p.id,
                        label: p.firstName + (" " + p.lastName)
                      };
              }));
}

function toMinutes(value) {
  var range = value.split(":");
  var hour = Belt_Array.get(range, 0);
  var minutes = Belt_Array.get(range, 1);
  if (hour !== undefined && minutes !== undefined) {
    return Math.imul(Caml_format.caml_int_of_string(hour), 60) + Caml_format.caml_int_of_string(minutes) | 0;
  } else {
    return 0;
  }
}

function computeDate(from_, to_, date) {
  if (date === undefined) {
    return [
            "",
            ""
          ];
  }
  var date$1 = Caml_option.valFromOption(date);
  var from_$1 = toMinutes(from_);
  var to_$1 = toMinutes(to_);
  return [
          DateFns.getTime(DateFns.addMinutes(DateFns.startOfDay(date$1), from_$1)).toString(),
          DateFns.getTime(DateFns.addMinutes(DateFns.startOfDay(date$1), to_$1)).toString()
        ];
}

function Calendar_AddVisit(Props) {
  var patientId = Props.patientId;
  var visible = Props.visible;
  var onClose = Props.onClose;
  var date = Props.date;
  var patients = Props.patients;
  var loading = Props.loading;
  var onSubmit = Props.onSubmit;
  var patient = Select$Peaky.use(undefined);
  var match = React.useState(function () {
        return "";
      });
  var setFrom = match[1];
  var from_ = match[0];
  var match$1 = React.useState(function () {
        return "";
      });
  var setTo = match$1[1];
  var to_ = match$1[0];
  var match$2 = React.useState(function () {
        return "";
      });
  var setNotes = match$2[1];
  var notes = match$2[0];
  React.useEffect((function () {
          if (date !== undefined) {
            var date$1 = Caml_option.valFromOption(date);
            var hours = DateFns.format(date$1, "HH");
            var minutes = DateFns.format(date$1, "mm");
            Curry._1(setFrom, (function (param) {
                    return hours + (":" + minutes);
                  }));
          }
          
        }), [date]);
  React.useEffect((function () {
          var p = Belt_Array.get(Belt_Array.keep(toSelectOptions(patients), (function (p) {
                      return Caml_obj.caml_equal(p.value, patientId);
                    })), 0);
          if (p !== undefined) {
            Curry._1(patient.setValue, p);
            Curry._1(patient.setSearch, p.label);
          }
          
        }), [
        patientId,
        patients
      ]);
  return React.createElement(SideNav$Peaky.make, {
              visible: visible,
              onClose: onClose,
              title: "Dodaj wizytę",
              children: null
            }, React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Select$Peaky.make, {
                        value: patient.value,
                        search: patient.search,
                        onSearchChange: patient.setSearch,
                        placeholder: "Wybierz pacjenta",
                        icon: React.createElement(ReactFeather.User, {
                              size: "20"
                            }),
                        visible: patient.visible,
                        onVisibleChange: patient.setVisible,
                        options: toSelectOptions(patients),
                        onChange: patient.setValue
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: from_,
                        onChange: (function (v) {
                            return Curry._1(setFrom, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "00:00",
                        icon: React.createElement(ReactFeather.Clock, {
                              size: "20"
                            })
                      }),
                  label: "Od"
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: to_,
                        onChange: (function (v) {
                            return Curry._1(setTo, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "00:00",
                        icon: React.createElement(ReactFeather.Clock, {
                              size: "20"
                            })
                      }),
                  label: "Do"
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.Textarea.make, {
                        placeholder: "Notatki",
                        value: notes,
                        onChange: (function (v) {
                            return Curry._1(setNotes, (function (param) {
                                          return v;
                                        }));
                          })
                      })
                }), React.createElement(Button$Peaky.Row.make, {
                  children: React.createElement(Button$Peaky.CTA.make, {
                        loading: loading,
                        children: React.createElement(Text$Peaky.make, {
                              children: "Dodaj wizytę"
                            }),
                        onClick: (function (param) {
                            var match = computeDate(from_, to_, date);
                            var match$1 = patient.value;
                            if (match$1 !== undefined) {
                              Curry._4(onSubmit, match$1.value, match[0], match[1], notes);
                              Curry._1(setNotes, (function (param) {
                                      return "";
                                    }));
                              Curry._1(setTo, (function (param) {
                                      return "";
                                    }));
                              Curry._1(setFrom, (function (param) {
                                      return "";
                                    }));
                              Curry._1(patient.setValue, undefined);
                              return Curry._1(patient.setSearch, "");
                            }
                            
                          })
                      })
                }));
}

var make = Calendar_AddVisit;

export {
  toSelectOptions ,
  toMinutes ,
  computeDate ,
  make ,
  
}
/* react Not a pure module */
