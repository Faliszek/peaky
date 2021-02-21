

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as ReactDom from "react-dom";
import * as Text$Peaky from "./Text.bs.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as Button$Peaky from "./Button.bs.js";

function Modal(Props) {
  var visible = Props.visible;
  var onVisibleChange = Props.onVisibleChange;
  var titleOpt = Props.title;
  var childrenOpt = Props.children;
  var onOkOpt = Props.onOk;
  var loadingOpt = Props.loading;
  var title = titleOpt !== undefined ? titleOpt : "Dodaj symptom";
  var children = childrenOpt !== undefined ? Caml_option.valFromOption(childrenOpt) : null;
  var onOk = onOkOpt !== undefined ? onOkOpt : (function (param) {
        
      });
  var loading = loadingOpt !== undefined ? loadingOpt : false;
  var modal = visible ? React.createElement("div", {
          className: "w-screen h-screen fixed top-0 left-0 z-10 flex items-center justify-center",
          style: {
            backgroundColor: "rgba(0,0,0,0.1)"
          }
        }, React.createElement("div", {
              className: "w-64 bg-white shadow-xl rounded-xl px-6 border border-gray-200 py-8 ",
              style: {
                width: "600px"
              }
            }, React.createElement("div", {
                  className: "text-2xl text-gray-600 mb-4"
                }, React.createElement(Text$Peaky.make, {
                      children: title
                    })), React.createElement("div", undefined, children), React.createElement("div", {
                  className: "flex justify-end gap-3"
                }, React.createElement(Button$Peaky.CTA.make, {
                      children: React.createElement(Text$Peaky.make, {
                            children: "Anuluj"
                          }),
                      type_: "ghost",
                      onClick: (function (param) {
                          return Curry._1(onVisibleChange, false);
                        })
                    }), React.createElement(Button$Peaky.CTA.make, {
                      loading: loading,
                      children: React.createElement(Text$Peaky.make, {
                            children: "Dodaj"
                          }),
                      onClick: (function (param) {
                          return Curry._1(onOk, undefined);
                        })
                    })))) : null;
  var el = document.querySelector("body");
  if (el == null) {
    return null;
  } else {
    return ReactDom.createPortal(modal, el);
  }
}

var make = Modal;

export {
  make ,
  
}
/* react Not a pure module */
