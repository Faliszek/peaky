

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as Text$Peaky from "./Text.bs.js";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";

function Input$Wrap(Props) {
  var children = Props.children;
  var label = Props.label;
  if (label !== undefined) {
    return React.createElement("div", {
                className: "mb-6"
              }, React.createElement("span", {
                    className: " text-lg mb-1 ml-2"
                  }, React.createElement(Text$Peaky.make, {
                        children: label
                      })), children);
  } else {
    return React.createElement("div", {
                className: "mb-6"
              }, children);
  }
}

var Wrap = {
  make: Input$Wrap
};

var focusCn = "outline-none focus:ring-2 focus:ring-green-400 focus:border-green-400";

function Input$Textarea(Props) {
  var placeholder = Props.placeholder;
  var ref_ = Props.ref_;
  var value = Props.value;
  var onChange = Props.onChange;
  var tmp = {
    className: Cn.$plus("p-4  w-full rounded-lg border text-lg text-gray-700  mr-4", focusCn),
    placeholder: placeholder,
    value: value,
    onChange: (function (e) {
        return Curry._1(onChange, e.target.value);
      })
  };
  if (ref_ !== undefined) {
    tmp.ref = Caml_option.valFromOption(ref_);
  }
  return React.createElement("textarea", tmp);
}

var Textarea = {
  make: Input$Textarea
};

function callSome(func) {
  Belt_Option.map(func, (function (f) {
          return Curry._1(f, undefined);
        }));
  
}

function Input(Props) {
  var value = Props.value;
  var onChange = Props.onChange;
  var placeholder = Props.placeholder;
  var type_ = Props.type_;
  var icon = Props.icon;
  var onFocus = Props.onFocus;
  var onBlur = Props.onBlur;
  var zIndex = Props.zIndex;
  var match = React.useState(function () {
        return false;
      });
  var setFocus = match[1];
  var style = zIndex !== undefined ? ({
        zIndex: zIndex.toString()
      }) : undefined;
  var input = function (cn, param) {
    var tmp = {
      className: Cn.$plus(Cn.$plus("shadow-md  text-gray-700  border border-gray-100 rounded-lg px-4 py-2 text-lg w-full h-12", Cn.mapSome(cn, (function (x) {
                      return x;
                    }))), focusCn),
      spellCheck: false,
      placeholder: placeholder,
      value: value,
      onFocus: (function (param) {
          Curry._1(setFocus, (function (param) {
                  return true;
                }));
          return callSome(onFocus);
        }),
      onBlur: (function (param) {
          Curry._1(setFocus, (function (param) {
                  return false;
                }));
          return callSome(onBlur);
        }),
      onChange: (function (e) {
          return Curry._1(onChange, e.target.value);
        })
    };
    if (type_ !== undefined) {
      tmp.type = Caml_option.valFromOption(type_);
    }
    return React.createElement("input", tmp);
  };
  if (icon === undefined) {
    return input(undefined, undefined);
  }
  var tmp = {
    className: "flex relative "
  };
  if (style !== undefined) {
    tmp.style = Caml_option.valFromOption(style);
  }
  return React.createElement("div", tmp, React.createElement("span", {
                  className: Cn.$plus("absolute top-0 left-0 w-12 h-12  flex items-center justify-center border-r", Cn.on("border-green-400 text-green-400", match[0]))
                }, Caml_option.valFromOption(icon)), input("pl-16", undefined));
}

var make = Input;

export {
  Wrap ,
  focusCn ,
  Textarea ,
  callSome ,
  make ,
  
}
/* react Not a pure module */
