

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as DateFns from "date-fns";
import * as Auth$Peaky from "./Auth.bs.js";
import * as Belt_Array from "@rescript/std/lib/es6/belt_Array.js";
import * as Page$Peaky from "./components/Page.bs.js";
import * as Time$Peaky from "./bindings/Time.bs.js";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Caml_format from "@rescript/std/lib/es6/caml_format.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as Avatar$Peaky from "./components/Avatar.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Router$Peaky from "./Router.bs.js";
import * as Request$Peaky from "./Request.bs.js";
import * as Spinner$Peaky from "./components/Spinner.bs.js";
import * as ReactFeather from "react-feather";
import * as Calendar_Query$Peaky from "./Calendar_Query.bs.js";
import * as Visit_Mutation$Peaky from "./Visit_Mutation.bs.js";
import * as Calendar_AddVisit$Peaky from "./Calendar_AddVisit.bs.js";

var hours = {
  start: 8,
  end_: 16
};

function makeDays(now) {
  return [
          DateFns.subDays(now, 2),
          DateFns.subDays(now, 1),
          now,
          DateFns.addDays(now, 1),
          DateFns.addDays(now, 2)
        ];
}

function makeHours(param) {
  return Belt_Array.range(hours.start, hours.end_);
}

function isToday(date) {
  var today = DateFns.startOfDay(Time$Peaky.now(undefined));
  return DateFns.getTime(today) === DateFns.getTime(date);
}

function Calendar$Visit(Props) {
  var id = Props.id;
  var from_ = Props.from_;
  var to_ = Props.to_;
  var patientId = Props.patientId;
  var patients = Props.patients;
  var days = Props.days;
  var from_$1 = Caml_format.caml_float_of_string(from_);
  var to_$1 = Caml_format.caml_float_of_string(to_);
  var fromDate = new Date(from_$1);
  var toDate = new Date(to_$1);
  var absoluteTop = ((Math.imul(DateFns.getHours(fromDate), 60) + DateFns.getMinutes(fromDate) | 0) << 1);
  var top = (absoluteTop - 960 | 0) + 60 | 0;
  (96).toString() + "px";
  var durationAsHeight = (DateFns.differenceInMinutes(to_$1, from_$1) << 1);
  var patient = Belt_Array.get(Belt_Array.keep(patients, (function (p) {
              return p.id === patientId;
            })), 0);
  var color = Belt_Option.getWithDefault(Belt_Option.map(patient, (function (p) {
              return p.color;
            })), "blue");
  var first = Belt_Option.map(Belt_Array.get(days, 0), (function (prim) {
          return prim.valueOf();
        }));
  var last = Belt_Option.map(Belt_Option.map(Belt_Array.get(days, 4), (function (prim) {
              return DateFns.endOfDay(prim);
            })), (function (prim) {
          return prim.valueOf();
        }));
  var match = React.useState(function () {
        
      });
  var setWidth = match[1];
  var width = match[0];
  var index = days.findIndex(function (d) {
        return DateFns.startOfDay(d).valueOf() === DateFns.startOfDay(fromDate).valueOf();
      });
  var visible = Belt_Option.isSome(width) ? "opacity-100" : "opacity-0";
  var left = width !== undefined ? 96 + width * index : 96;
  var userId = Auth$Peaky.getUserId(undefined);
  if (first === undefined) {
    return null;
  }
  if (last === undefined) {
    return null;
  }
  if (!(from_$1 > first && from_$1 < last)) {
    return null;
  }
  var tmp;
  if (patient !== undefined) {
    var lastName = patient.lastName;
    var firstName = patient.firstName;
    var name = firstName + (" " + lastName);
    tmp = React.createElement("div", {
          className: "flex items-center"
        }, React.createElement(Avatar$Peaky.make, {
              firstName: firstName,
              lastName: lastName,
              size: "small",
              color: patient.color
            }), React.createElement("div", {
              className: "ml-2 flex flex-col"
            }, React.createElement("span", {
                  className: "text-md"
                }, name), React.createElement("span", {
                  className: "text-sm text-gray-400"
                }, patient.disease)));
  } else {
    tmp = null;
  }
  return React.createElement("div", {
              ref: (function (el) {
                  Belt_Option.map((el == null) ? undefined : Caml_option.some(el), (function (el) {
                          return Curry._1(setWidth, (function (param) {
                                        return el.offsetWidth;
                                      }));
                        }));
                  
                }),
              className: Cn.$plus("absolute rounded-lg shadow-md bg-white cursor-pointer border-blue-400 border flex flex-col", visible),
              style: {
                borderColor: color,
                height: durationAsHeight.toString() + "px",
                left: left.toString() + "px",
                top: top.toString() + "px",
                width: "calc( (100% - $leftCellWidth) / 5)"
              }
            }, React.createElement("div", {
                  className: "bg-blue-400 w-full h-8 rounded-t-md flex items-center p-2",
                  style: {
                    backgroundColor: color
                  }
                }, React.createElement("span", {
                      className: "text-white font-bold"
                    }, DateFns.format(fromDate, "HH:mm"), " - ", DateFns.format(toDate, "HH:mm"))), React.createElement("div", {
                  className: "flex h-full"
                }, React.createElement("div", {
                      className: "flex-2 p-2  h-full"
                    }, tmp), React.createElement("div", {
                      className: "flex flex-1 p-2  items-end justify-end h-full"
                    }, React.createElement(Button$Peaky.SmallRound.make, {
                          icon: React.createElement(ReactFeather.Phone, {}),
                          onClick: (function (param) {
                              return Router$Peaky.push({
                                          TAG: /* Visit */4,
                                          _0: id,
                                          _1: userId,
                                          _2: patientId
                                        });
                            })
                        }))));
}

var Visit = {
  make: Calendar$Visit
};

function Calendar(Props) {
  var match = React.useState(function () {
        return DateFns.startOfDay(Time$Peaky.now(undefined));
      });
  var setNow = match[1];
  var now = match[0];
  var match$1 = React.useState(function () {
        return false;
      });
  var setVisible = match$1[1];
  var match$2 = React.useState(function () {
        
      });
  var setDate = match$2[1];
  var days = makeDays(now);
  var hours = makeHours(undefined);
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
  var match$3 = Curry.app(Visit_Mutation$Peaky.Mutation.use, [
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
  var createVisit = match$3[0];
  var data = query.data;
  var data$1 = query.data;
  return React.createElement(Page$Peaky.make, {
              title: "Kalendarz",
              children: null
            }, React.createElement("div", {
                  className: "flex items-center justify-center pb-8 text-xl pl-24 "
                }, React.createElement(Button$Peaky.Nav.make, {
                      onClick: (function (param) {
                          return Curry._1(setNow, (function (now) {
                                        return DateFns.subDays(now, 5);
                                      }));
                        }),
                      children: React.createElement(ReactFeather.ChevronLeft, {
                            size: "32"
                          })
                    }), React.createElement("span", {
                      className: "select-none mx-4 block"
                    }, Belt_Option.getWithDefault(Belt_Option.map(Belt_Array.get(days, 0), (function (__x) {
                                return DateFns.format(__x, "dd.MM");
                              })), ""), "  -  ", Belt_Option.getWithDefault(Belt_Option.map(Belt_Array.get(days, days.length - 1 | 0), (function (__x) {
                                return DateFns.format(__x, "dd.MM");
                              })), "")), React.createElement(Button$Peaky.Nav.make, {
                      onClick: (function (param) {
                          return Curry._1(setNow, (function (now) {
                                        return DateFns.addDays(now, 5);
                                      }));
                        }),
                      children: React.createElement(ReactFeather.ChevronRight, {
                            size: "32"
                          })
                    })), React.createElement("div", {
                  className: "flex border flex-wrap rounded-lg relative "
                }, React.createElement("div", {
                      className: "flex w-full bg-gray-50",
                      style: {
                        height: (60).toString() + "px"
                      }
                    }, React.createElement("div", {
                          className: "w-24"
                        }), Belt_Array.map(days, (function (d) {
                            return React.createElement("div", {
                                        key: DateFns.format(d, "dd.mm"),
                                        className: Cn.$plus("flex-1  text-lg text-center py-4", Cn.on("text-green-500 font-bold bg-green-100  ring-2 ring-green-300 z-10 rounded-md", isToday(d)))
                                      }, DateFns.format(d, "dd.MM"));
                          }))), Belt_Array.map(hours, (function (h) {
                        return React.createElement("div", {
                                    key: h.toString(),
                                    className: "flex w-full"
                                  }, React.createElement("div", {
                                        className: "w-24 border-t",
                                        style: {
                                          width: (96).toString() + "px"
                                        }
                                      }, React.createElement("div", {
                                            key: h.toString(),
                                            className: "text-center h-32 flex justify-center text-lg",
                                            style: {
                                              height: (120).toString() + "px"
                                            }
                                          }, React.createElement("span", {
                                                className: "mt-2"
                                              }, DateFns.format(DateFns.addHours(now, h), "HH:mm")))), Belt_Array.map(days, (function (d) {
                                          var date = DateFns.addHours(d, h);
                                          return React.createElement("div", {
                                                      key: DateFns.getTime(date).toString(),
                                                      className: "group flex-1 border-l border-t cursor-pointer transition-shadow hover:shadow-inner",
                                                      onClick: (function (param) {
                                                          Curry._1(setVisible, (function (param) {
                                                                  return true;
                                                                }));
                                                          return Curry._1(setDate, (function (param) {
                                                                        return Caml_option.some(date);
                                                                      }));
                                                        })
                                                    }, React.createElement("span", {
                                                          className: "p-4 block text-xl opacity-0 transition-opacity group-hover:opacity-50 "
                                                        }, DateFns.format(date, "HH:mm")));
                                        })));
                      })), query.loading ? React.createElement("div", {
                        className: "absolute w-full h-full flex pt-48 justify-center bg-white opacity-80"
                      }, React.createElement(Spinner$Peaky.make, {
                            tip: "Trwa wczytywanie "
                          })) : (
                    data !== undefined ? React.createElement("div", undefined, Belt_Array.map(data.visits, (function (v) {
                                  return React.createElement(Calendar$Visit, {
                                              id: v.id,
                                              from_: v.from_,
                                              to_: v.to_,
                                              patientId: v.patientId,
                                              patients: data.patients,
                                              days: days,
                                              key: v.id
                                            });
                                }))) : null
                  )), data$1 !== undefined ? React.createElement(Calendar_AddVisit$Peaky.make, {
                    visible: match$1[0],
                    onClose: (function (param) {
                        return Curry._1(setVisible, (function (param) {
                                      return false;
                                    }));
                      }),
                    date: match$2[0],
                    patients: data$1.patients,
                    loading: match$3[1].loading,
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
                  }) : null);
}

var daysInCalendar = 5;

var rowHeight = 60;

var hourWidth = 96;

var make = Calendar;

export {
  daysInCalendar ,
  hours ,
  makeDays ,
  makeHours ,
  isToday ,
  rowHeight ,
  hourWidth ,
  Visit ,
  make ,
  
}
/* react Not a pure module */
