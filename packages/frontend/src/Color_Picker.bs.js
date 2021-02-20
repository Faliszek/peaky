

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "@rescript/std/lib/es6/belt_Array.js";

var colors = [
  "#F87171",
  "#FB923C",
  "#FBBF24",
  "#FACC15",
  "#A3E635",
  "#4ADE80",
  "#34D399",
  "#2DD4BF",
  "#22D3EE",
  "#38BDF8",
  "#60A5FA",
  "#818CF8",
  "#A78BFA",
  "#C084FC",
  "#F5D0FE"
];

function Color_Picker(Props) {
  var value = Props.value;
  var onChange = Props.onChange;
  var className = Props.className;
  return React.createElement("div", {
              className: Cn.$plus("mb-12 mt-8 flex flex-wrap gap-4", Cn.mapSome(className, (function (x) {
                          return x;
                        })))
            }, Belt_Array.map(colors, (function (c) {
                    var active = value === c ? "ring-4 ring-green-400" : "";
                    return React.createElement("div", {
                                key: c,
                                className: Cn.$plus("w-10 h-10 rounded-md shadow-md border border-gray-100 cursor-pointer", active),
                                style: {
                                  backgroundColor: c
                                },
                                onClick: (function (param) {
                                    return Curry._1(onChange, c);
                                  })
                              });
                  })));
}

var make = Color_Picker;

export {
  colors ,
  make ,
  
}
/* react Not a pure module */
