

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as React from "react";
import * as Text$Peaky from "./Text.bs.js";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";

function Avatar(Props) {
  var avatar = Props.avatar;
  var firstName = Props.firstName;
  var lastName = Props.lastName;
  var sizeOpt = Props.size;
  var color = Props.color;
  var size = sizeOpt !== undefined ? sizeOpt : "default";
  var color$1 = Belt_Option.getWithDefault(color, "green");
  var fontSize = size === "big" ? "text-6xl" : (
      size === "default" ? "text-3xl" : "text-sm"
    );
  var size$1 = size === "big" ? "w-48 h-48" : (
      size === "default" ? "w-24 h-24 " : "w-8 h-8"
    );
  if (avatar !== undefined) {
    return React.createElement("img", {
                className: Cn.$plus("rounded-full shadow-md border border-gray-100", size$1),
                src: avatar
              });
  } else if (firstName !== undefined && lastName !== undefined) {
    return React.createElement("div", {
                className: Cn.$plus("rounded-full shadow-md border-border-gray flex items-center justify-center bg-green-300", size$1),
                style: {
                  backgroundColor: color$1,
                  filter: "contrast(90%)"
                }
              }, React.createElement("span", {
                    className: Cn.$plus("text-white", fontSize)
                  }, React.createElement(Text$Peaky.make, {
                        children: firstName[0] + lastName[0]
                      })));
  } else {
    return null;
  }
}

var make = Avatar;

export {
  make ,
  
}
/* react Not a pure module */
