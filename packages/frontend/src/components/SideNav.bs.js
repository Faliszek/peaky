

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Text$Peaky from "./Text.bs.js";
import * as Button$Peaky from "./Button.bs.js";
import * as ReactFeather from "react-feather";

function SideNav(Props) {
  var visible = Props.visible;
  var onClose = Props.onClose;
  var title = Props.title;
  var children = Props.children;
  return React.createElement("div", {
              className: Cn.$plus("fixed right-0 top-0 z-40 h-screen w-96 p-8 shadow-xl bg-white transform transition-transform", Cn.on("translate-x-96", !visible))
            }, React.createElement("div", {
                  className: "mb-8 flex items-center "
                }, React.createElement(Button$Peaky.Nav.make, {
                      onClick: (function (param) {
                          return Curry._1(onClose, undefined);
                        }),
                      children: React.createElement(ReactFeather.ArrowLeft, {})
                    }), React.createElement("span", {
                      className: "text-xl block ml-4 "
                    }, React.createElement(Text$Peaky.make, {
                          children: title
                        }))), children);
}

var make = SideNav;

export {
  make ,
  
}
/* react Not a pure module */
