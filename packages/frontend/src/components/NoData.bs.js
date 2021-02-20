

import * as React from "react";
import * as Text$Peaky from "./Text.bs.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as Button$Peaky from "./Button.bs.js";
import * as ReactFeather from "react-feather";

function NoData(Props) {
  var buttonText = Props.buttonText;
  var buttonIcon = Props.buttonIcon;
  var onButtonClick = Props.onButtonClick;
  var title = Props.title;
  var text = Props.text;
  var iconOpt = Props.icon;
  var icon = iconOpt !== undefined ? Caml_option.valFromOption(iconOpt) : React.createElement(ReactFeather.Inbox, {
          size: "64"
        });
  return React.createElement("div", {
              className: "flex flex-col justify-center items-center py-40 h-full"
            }, React.createElement("span", {
                  className: "text-6xl text-gray-400"
                }, icon), React.createElement("h1", {
                  className: "text-gray-400 text-5xl mb-4 my-6 text-center"
                }, title), React.createElement("p", {
                  className: "text-gray-400 text-xl mb-10 text-center"
                }, text), React.createElement("div", undefined, buttonText !== undefined && buttonIcon !== undefined && onButtonClick !== undefined ? React.createElement(Button$Peaky.CTA.make, {
                        children: React.createElement(Text$Peaky.make, {
                              children: buttonText
                            }),
                        icon: Caml_option.valFromOption(buttonIcon),
                        onClick: onButtonClick
                      }) : null));
}

var make = NoData;

export {
  make ,
  
}
/* react Not a pure module */
