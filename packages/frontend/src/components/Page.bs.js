

import * as React from "react";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as Button$Peaky from "./Button.bs.js";
import * as ReactFeather from "react-feather";

function Page$Block(Props) {
  var children = Props.children;
  return React.createElement("div", {
              className: "shadow-sm p-8"
            }, children);
}

var Block = {
  make: Page$Block
};

function Page(Props) {
  var title = Props.title;
  var children = Props.children;
  var hasBackButtonOpt = Props.hasBackButton;
  var actions = Props.actions;
  var hasBackButton = hasBackButtonOpt !== undefined ? hasBackButtonOpt : false;
  var actionsStyle = Belt_Option.isSome(actions) ? "flex justify-between" : "";
  return React.createElement("div", {
              className: "px-8 py-8  min-h-full"
            }, React.createElement("div", {
                  className: "px-4 pb-4  bg-white rounded-lg"
                }, React.createElement("div", {
                      className: actionsStyle
                    }, React.createElement("div", {
                          className: "flex items-center text-2xl text-gray-700 mb-8"
                        }, hasBackButton ? React.createElement(Button$Peaky.Nav.make, {
                                onClick: (function (param) {
                                    history.back();
                                    
                                  }),
                                children: React.createElement(ReactFeather.ArrowLeft, {}),
                                className: "mr-4"
                              }) : null, title), actions !== undefined ? React.createElement("div", undefined, Caml_option.valFromOption(actions)) : null), React.createElement("div", {
                      className: "text-gray-600"
                    }, children)));
}

var make = Page;

export {
  Block ,
  make ,
  
}
/* react Not a pure module */
