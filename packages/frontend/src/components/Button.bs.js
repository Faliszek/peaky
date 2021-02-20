

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as React from "react";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as ReactFeather from "react-feather";

function Button(Props) {
  var children = Props.children;
  var icon = Props.icon;
  var onClick = Props.onClick;
  var className = Props.className;
  var tmp = {
    className: Cn.$plus("px-4 py-2 border-green-500 border text-green-500 font-medium rounded-md transition-colors hover:text-white hover hover:bg-green-500 flex items-center", Cn.mapSome(className, (function (x) {
                return x;
              })))
  };
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("button", tmp, React.createElement("span", {
                  className: Cn.mapSome(icon, (function (param) {
                          return "mr-2";
                        }))
                }, children), Belt_Option.getWithDefault(icon, null));
}

function Button$Row(Props) {
  var children = Props.children;
  return React.createElement("div", {
              className: "flex justify-center "
            }, children);
}

var Row = {
  make: Button$Row
};

function Button$Round(Props) {
  var icon = Props.icon;
  var onClick = Props.onClick;
  var className = Props.className;
  var tmp = {
    className: Cn.$plus("rounded-full  w-24 h-24 flex items-center justify-center shadow-md  cursor-pointer transition-colors  focus:outline-none", Cn.mapSome(className, (function (x) {
                return x;
              })))
  };
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("button", tmp, icon);
}

var Round = {
  make: Button$Round
};

function Button$SmallRound(Props) {
  var icon = Props.icon;
  var onClick = Props.onClick;
  var className = Props.className;
  var tmp = {
    className: Cn.$plus("rounded-full bg-green-500 w-12 h-12 flex items-center justify-center shadow-md text-white cursor-pointer transition-colors hover:bg-green-400 focus:outline-none", Cn.mapSome(className, (function (x) {
                return x;
              })))
  };
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("button", tmp, icon);
}

var SmallRound = {
  make: Button$SmallRound
};

function Button$CallButton(Props) {
  var icon = Props.icon;
  var onClick = Props.onClick;
  var className = Props.className;
  var tmp = {
    className: Cn.$plus("rounded-full  w-12 h-12 flex items-center justify-center shadow-md text-white cursor-pointer transition-colors  focus:outline-none", Cn.mapSome(className, (function (x) {
                return x;
              })))
  };
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("button", tmp, icon);
}

var CallButton = {
  make: Button$CallButton
};

function Button$Nav(Props) {
  var onClick = Props.onClick;
  var children = Props.children;
  var className = Props.className;
  return React.createElement("div", {
              className: Cn.$plus("p-2 cursor-pointer rounded-lg bg-white transition-colors hover:bg-gray-100", Cn.mapSome(className, (function (x) {
                          return x;
                        }))),
              onClick: onClick
            }, children);
}

var Nav = {
  make: Button$Nav
};

function Button$CTA(Props) {
  var htmlType = Props.htmlType;
  var loadingOpt = Props.loading;
  var children = Props.children;
  var className = Props.className;
  var icon = Props.icon;
  var type_Opt = Props.type_;
  var onClick = Props.onClick;
  var disabledOpt = Props.disabled;
  var loading = loadingOpt !== undefined ? loadingOpt : false;
  var type_ = type_Opt !== undefined ? type_Opt : "primary";
  var disabled = disabledOpt !== undefined ? disabledOpt : false;
  var colors = disabled ? "border border-gray-400 bg-gray-400 text-white cursor-not-allowed" : (
      type_ === "ghost" ? "border border-green-400 bg-white  text-green-400 hover:text-green-300 hover:border-green-300 shadow-lg" : "border border-green-400 bg-green-400  text-white hover:bg-green-300 hover:border-green-300 shadow-lg"
    );
  var tmp = {
    className: Cn.$plus(Cn.$plus("relative px-8 h-12   flex items-center justify-center text-lg rounded-3xl focus:outline-none transition-colors  overflow-hidden", colors), Cn.mapSome(className, (function (x) {
                return x;
              })))
  };
  if (htmlType !== undefined) {
    tmp.type = Caml_option.valFromOption(htmlType);
  }
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("button", tmp, Belt_Option.getWithDefault(icon, null), children, React.createElement("span", {
                  className: Cn.$plus("w-full h-full flex items-center justify-center  transition-opacity absolute top-0 left-0 bg-green-50  rounded-3xl ring-green-800 focus:ring-2", loading ? "opacity-100" : "opacity-0")
                }, React.createElement(ReactFeather.Loader, {
                      className: "animate-spin text-green-400"
                    })));
}

var CTA = {
  make: Button$CTA
};

var make = Button;

export {
  make ,
  Row ,
  Round ,
  SmallRound ,
  CallButton ,
  Nav ,
  CTA ,
  
}
/* react Not a pure module */
