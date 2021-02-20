

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as React from "react";

function Spinner(Props) {
  var sizeOpt = Props.size;
  var className = Props.className;
  var colorOpt = Props.color;
  var tip = Props.tip;
  var size = sizeOpt !== undefined ? sizeOpt : "medium";
  var color = colorOpt !== undefined ? colorOpt : "green";
  var size$1 = size === "small" ? "w-5 h-5 p-2" : "w-12 h-12";
  var color$1 = color === "green" ? "border-green-500" : "border-white";
  var spinner = React.createElement("div", {
        className: Cn.$plus(Cn.$plus(Cn.$plus("border-green  border-t-2 animate-spin-fast rounded-full", color$1), size$1), Cn.mapSome(className, (function (c) {
                    return c;
                  })))
      });
  if (tip !== undefined) {
    return React.createElement("div", {
                className: "flex items-center flex-col"
              }, spinner, React.createElement("span", {
                    className: "ml-2 text-gray-700"
                  }, tip));
  } else {
    return spinner;
  }
}

var make = Spinner;

export {
  make ,
  
}
/* react Not a pure module */
