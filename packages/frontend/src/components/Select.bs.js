

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Text$Peaky from "./Text.bs.js";
import * as Input$Peaky from "./Input.bs.js";
import * as ReactFeather from "react-feather";

function useOutsideClick(el, visible, onOutsideClick) {
  React.useEffect((function () {
          var onOutsideClick$1 = function ($$event) {
            var match = el.current;
            if (!(match == null) && visible && !match.contains($$event.target)) {
              return Curry._1(onOutsideClick, undefined);
            }
            
          };
          window.addEventListener("click", onOutsideClick$1);
          return (function (param) {
                    window.addEventListener("click", onOutsideClick$1);
                    
                  });
        }), [
        el,
        visible
      ]);
  
}

var initialState = {
  search: "",
  value: undefined,
  visible: false
};

function reducer(state, action) {
  switch (action.TAG | 0) {
    case /* SetVisibility */0 :
        return {
                search: state.search,
                value: state.value,
                visible: action._0
              };
    case /* SetSearch */1 :
        return {
                search: action._0,
                value: state.value,
                visible: state.visible
              };
    case /* SetValue */2 :
        return {
                search: state.search,
                value: action._0,
                visible: state.visible
              };
    
  }
}

function use(param) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  return {
          search: state.search,
          value: state.value,
          visible: state.visible,
          setValue: (function (v) {
              return Curry._1(dispatch, {
                          TAG: /* SetValue */2,
                          _0: v
                        });
            }),
          setSearch: (function (v) {
              return Curry._1(dispatch, {
                          TAG: /* SetSearch */1,
                          _0: v
                        });
            }),
          setVisible: (function (v) {
              return Curry._1(dispatch, {
                          TAG: /* SetVisibility */0,
                          _0: v
                        });
            })
        };
}

function Select(Props) {
  var value = Props.value;
  var search = Props.search;
  var onSearchChange = Props.onSearchChange;
  var placeholder = Props.placeholder;
  var icon = Props.icon;
  var visible = Props.visible;
  var onVisibleChange = Props.onVisibleChange;
  var options = Props.options;
  var onChange = Props.onChange;
  var loadingOpt = Props.loading;
  var loading = loadingOpt !== undefined ? loadingOpt : false;
  var filterOptions = value !== undefined || search === "" ? options : Belt_Array.keep(options, (function (o) {
            return o.label.includes(search);
          }));
  var selectRef = React.useRef(null);
  var noOptions = options.length === 0;
  var match;
  if (loading || noOptions) {
    match = [
      "44px",
      "44px"
    ];
  } else {
    var calc = function (x) {
      return (Math.imul(x, 44) + 20 | 0).toString() + "px";
    };
    match = [
      calc(10),
      calc(filterOptions.length)
    ];
  }
  useOutsideClick(selectRef, visible, (function (param) {
          return Curry._1(onVisibleChange, false);
        }));
  return React.createElement("div", {
              ref: selectRef,
              className: "relative"
            }, React.createElement("div", {
                  className: Cn.$plus("absolute border border-b border-l border-r bg-white rounded-lg w-full overflow-y-scroll transition-transform transform-gpu scale-y-0  origin-top", Cn.on("shadow-md  scale-y-100", visible)),
                  style: {
                    height: match[1],
                    maxHeight: match[0],
                    paddingTop: "10px",
                    paddingBottom: "10px",
                    top: "40px",
                    zIndex: (30).toString()
                  }
                }, loading ? React.createElement("div", {
                        className: "flex items-center justify-center py-2 text-gray-300 text-lg"
                      }, React.createElement(ReactFeather.Loader, {
                            className: "animate-spin"
                          })) : (
                    noOptions ? React.createElement("div", {
                            className: "flex items-center justify-center text-gray-300 text-lg"
                          }, React.createElement(Text$Peaky.make, {
                                children: "Brak danych"
                              })) : Belt_Array.map(filterOptions, (function (o) {
                              var active = Caml_obj.caml_equal(o, value) ? "bg-green-500 text-white" : "bg-white";
                              return React.createElement("div", {
                                          key: o.value,
                                          className: Cn.$plus("text-lg py-2 px-16 cursor-pointer bg-white hover:bg-gray-100 ", active),
                                          onClick: (function (param) {
                                              Curry._1(onChange, o);
                                              Curry._1(onSearchChange, o.label);
                                              return Curry._1(onVisibleChange, false);
                                            })
                                        }, React.createElement(Text$Peaky.make, {
                                              children: o.label
                                            }));
                            }))
                  )), React.createElement(Input$Peaky.make, {
                  value: search,
                  onChange: (function (value) {
                      Curry._1(onSearchChange, value);
                      return Curry._1(onChange, undefined);
                    }),
                  placeholder: placeholder,
                  icon: icon,
                  onFocus: (function (param) {
                      return Curry._1(onVisibleChange, true);
                    }),
                  zIndex: 30
                }));
}

var make = Select;

export {
  useOutsideClick ,
  initialState ,
  reducer ,
  use ,
  make ,
  
}
/* react Not a pure module */
