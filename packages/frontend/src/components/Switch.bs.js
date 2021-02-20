

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReactFeather from "react-feather";

function Switch(Props) {
  var checked = Props.checked;
  var onChange = Props.onChange;
  var loadingOpt = Props.loading;
  var loading = loadingOpt !== undefined ? loadingOpt : false;
  var bg = loading || !checked ? "bg-gray-200" : "bg-green-400";
  var border = loading || !checked ? "border-gray-200" : "border-green-400";
  return React.createElement("label", {
              className: "flex items-center cursor-pointer"
            }, React.createElement("div", {
                  className: "relative"
                }, React.createElement("input", {
                      className: "hidden",
                      checked: checked,
                      type: "checkbox",
                      onChange: (function (param) {
                          if (!loading) {
                            return Curry._1(onChange, !checked);
                          }
                          
                        })
                    }), React.createElement("div", {
                      className: Cn.$plus("w-12 h-6 rounded-full shadow-inner transition-all", bg)
                    }), React.createElement("div", {
                      className: Cn.$plus(Cn.$plus("absolute w-6 h-6 bg-white rounded-full shadow-sm inset-y-0 left-0 transition-all border-2 transform flex items-center justify-center", border), Cn.on("translate-x-full", checked && !loading))
                    }, loading ? React.createElement(ReactFeather.Loader, {
                            size: "16",
                            className: "animate-spin text-gray-400 "
                          }) : null)), React.createElement("div", {
                  className: "ml-3 text-gray-700 font-medium"
                }));
}

var make = Switch;

export {
  make ,
  
}
/* react Not a pure module */
