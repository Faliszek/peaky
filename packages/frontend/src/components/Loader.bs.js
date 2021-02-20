

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReactDom from "react-dom";

function toState(prevState, loading) {
  if (prevState) {
    if (loading) {
      return /* Idle */2;
    } else {
      return /* FinishLoading */1;
    }
  } else if (loading) {
    return /* StartLoading */0;
  } else {
    return /* Idle */2;
  }
}

function useAnimate(loading) {
  var match = React.useState(function () {
        return loading;
      });
  var setPrevState = match[1];
  var prevState = match[0];
  var state = React.useMemo((function () {
          return toState(prevState, loading);
        }), [
        prevState,
        loading
      ]);
  var match$1 = React.useState(function () {
        return 0.0;
      });
  var setCn = match$1[1];
  React.useEffect((function () {
          Curry._1(setPrevState, (function (param) {
                  return loading;
                }));
          
        }), [loading]);
  React.useEffect((function () {
          switch (state) {
            case /* StartLoading */0 :
                setTimeout((function (param) {
                        return Curry._1(setCn, (function (param) {
                                      return 0.0;
                                    }));
                      }), 50);
                setTimeout((function (param) {
                        return Curry._1(setCn, (function (param) {
                                      return 0.25;
                                    }));
                      }), 100);
                setTimeout((function (param) {
                        return Curry._1(setCn, (function (param) {
                                      return 0.75;
                                    }));
                      }), 125);
                break;
            case /* FinishLoading */1 :
                Curry._1(setCn, (function (param) {
                        return 1.0;
                      }));
                setTimeout((function (param) {
                        return Curry._1(setCn, (function (param) {
                                      return 0.0;
                                    }));
                      }), 50);
                break;
            case /* Idle */2 :
                break;
            
          }
          
        }), [state]);
  return match$1[0].toString();
}

function Loader(Props) {
  var loadingOpt = Props.loading;
  var loading = loadingOpt !== undefined ? loadingOpt : false;
  var scaleX = useAnimate(loading);
  return ReactDom.createPortal(React.createElement("div", {
                  className: "fixed top-0 left-0 h-1 w-full z-20 scale"
                }, React.createElement("div", {
                      className: "bg-green-500 h-full w-full transform transition-transform origin-left ",
                      style: {
                        transform: "scaleX(" + scaleX + ")"
                      }
                    })), document.body);
}

var make = Loader;

export {
  toState ,
  useAnimate ,
  make ,
  
}
/* react Not a pure module */
