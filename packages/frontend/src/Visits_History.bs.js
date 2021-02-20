

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as React from "react";
import * as DateFns from "date-fns";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Time$Peaky from "./bindings/Time.bs.js";
import * as Table$Peaky from "./Table.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as ReactFeather from "react-feather";

function Visits_History(Props) {
  var calls = Props.calls;
  var callMode = Props.callMode;
  return React.createElement("div", {
              className: "shadow-md border border-gray-200 rounded-lg px-8"
            }, React.createElement("div", {
                  className: "flex w-full"
                }, React.createElement(Table$Peaky.Th.make, {
                      text: "Numer ID",
                      width: "w-1/6"
                    }), React.createElement(Table$Peaky.Th.make, {
                      text: "Czas trwania",
                      width: "w-1/5"
                    }), React.createElement(Table$Peaky.Th.make, {
                      text: "Data rozpoczęcia",
                      width: "w-1/5"
                    }), React.createElement(Table$Peaky.Th.make, {
                      text: "Pacjent",
                      width: "w-1/5"
                    }), React.createElement(Table$Peaky.Th.make, {
                      text: "Szczegóły",
                      width: "w-1/3"
                    })), React.createElement("div", {
                  className: "flex w-full flex-col"
                }, Belt_Array.map(calls, (function (c) {
                        var iconColor = c.answered ? "text-green-500" : "text-red-500";
                        var match = c.withWho;
                        return React.createElement("div", {
                                    key: c.id,
                                    className: "flex w-full border-t border-gray-300 items-center"
                                  }, React.createElement(Table$Peaky.Td.make, {
                                        width: "w-1/6 ",
                                        children: null
                                      }, React.createElement(Text$Peaky.make, {
                                            children: c.id
                                          }), React.createElement("span", {
                                            className: Cn.$plus("ml-2", iconColor)
                                          }, c.answered ? React.createElement(ReactFeather.PhoneCall, {}) : React.createElement(ReactFeather.PhoneMissed, {}))), React.createElement(Table$Peaky.Td.make, {
                                        width: "w-1/5",
                                        children: React.createElement(Text$Peaky.make, {
                                              children: DateFns.format(new Date(c.duration + DateFns.getTime(DateFns.startOfDay(Time$Peaky.now(undefined)))), "HH:mm")
                                            })
                                      }), React.createElement(Table$Peaky.Td.make, {
                                        width: "w-1/5",
                                        children: React.createElement(Text$Peaky.make, {
                                              children: DateFns.format(new Date(c.timestamp), "dd.MM.yyyy, HH:mm")
                                            })
                                      }), React.createElement(Table$Peaky.Td.make, {
                                        width: "w-1/5",
                                        children: match !== undefined && !callMode ? React.createElement(Text$Peaky.make, {
                                                children: match
                                              }) : "-"
                                      }), React.createElement(Table$Peaky.Td.make, {
                                        width: "w-1/3",
                                        children: React.createElement(Button$Peaky.CTA.make, {
                                              children: React.createElement(Text$Peaky.make, {
                                                    children: "Zobacz Szczegóły"
                                                  }),
                                              icon: React.createElement(ReactFeather.List, {
                                                    className: "mr-4"
                                                  })
                                            })
                                      }));
                      }))));
}

var make = Visits_History;

export {
  make ,
  
}
/* react Not a pure module */
