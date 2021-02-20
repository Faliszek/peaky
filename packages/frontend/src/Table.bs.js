

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as React from "react";
import * as Text$Peaky from "./components/Text.bs.js";

function Table$Th(Props) {
  var text = Props.text;
  var width = Props.width;
  return React.createElement("div", {
              className: Cn.$plus("px-4 py-6 text-lg font-bold text-gray-600 text-center", width)
            }, React.createElement(Text$Peaky.make, {
                  children: text
                }));
}

var Th = {
  make: Table$Th
};

function Table$Td(Props) {
  var width = Props.width;
  var children = Props.children;
  return React.createElement("div", {
              className: Cn.$plus("px-4 py-4 text-center text-lg flex items-center justify-center", width)
            }, children);
}

var Td = {
  make: Table$Td
};

export {
  Th ,
  Td ,
  
}
/* react Not a pure module */
