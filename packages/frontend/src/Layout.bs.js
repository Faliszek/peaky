

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as Belt_List from "bs-platform/lib/es6/belt_List.js";
import * as Auth$Peaky from "./Auth.bs.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Avatar$Peaky from "./components/Avatar.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Router$Peaky from "./Router.bs.js";
import * as ReactFeather from "react-feather";
import * as Client from "@apollo/client";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

function Layout$Menu$Item(Props) {
  var icon = Props.icon;
  var text = Props.text;
  var activeOpt = Props.active;
  var view = Props.view;
  var active = activeOpt !== undefined ? activeOpt : false;
  var className = active ? "bg-green-500 text-white  hover:text-white" : "text-green-600 bg-white  hover:text-green-500";
  return React.createElement("li", {
              className: "bg-white mb-1",
              onClick: (function (param) {
                  return Router$Peaky.push(view);
                })
            }, React.createElement("a", {
                  className: Cn.$plus("px-4 py-2 flex items-center font-medium transition-colors rounded-r-lg", className)
                }, icon, React.createElement(Text$Peaky.make, {
                      children: text
                    })));
}

var Item = {
  make: Layout$Menu$Item
};

function Layout$Menu(Props) {
  var firstName = Props.firstName;
  var lastName = Props.lastName;
  var url = ReasonReactRouter.useUrl(undefined, undefined);
  var match = url.path;
  var tmp;
  if (match && match.hd === "patients") {
    var match$1 = match.tl;
    if (match$1) {
      var match$2 = match$1.tl;
      tmp = match$2 && match$2.tl ? false : true;
    } else {
      tmp = true;
    }
  } else {
    tmp = false;
  }
  var match$3 = url.path;
  var tmp$1;
  if (match$3 && match$3.hd === "consultations") {
    var match$4 = match$3.tl;
    if (match$4) {
      var match$5 = match$4.tl;
      tmp$1 = match$5 && match$5.tl ? false : true;
    } else {
      tmp$1 = true;
    }
  } else {
    tmp$1 = false;
  }
  var tmp$2 = {};
  if (firstName !== undefined) {
    tmp$2.firstName = Caml_option.valFromOption(firstName);
  }
  if (lastName !== undefined) {
    tmp$2.lastName = Caml_option.valFromOption(lastName);
  }
  return React.createElement("nav", {
              className: "w-40  h-screen  bg-white border-r-2 border-gray-100 z-10 pr-1 flex flex-col justify-between fixed left-0 top-0"
            }, React.createElement("div", undefined, React.createElement("div", {
                      className: "flex justify-start ml-4"
                    }, React.createElement("div", {
                          className: "h-24 flex items-center justify-center mb-4"
                        }, React.createElement("span", {
                              className: " bg-green-500 p-3 rounded-full shadow-lg mr-2"
                            }, React.createElement(ReactFeather.Activity, {
                                  color: "white",
                                  size: "18"
                                })), React.createElement("span", {
                              className: "text-green-500 uppercase font-bold text-md"
                            }, React.createElement(Text$Peaky.make, {
                                  children: "Peaky"
                                })))), React.createElement("ul", {
                      className: "bg-white"
                    }, React.createElement(Layout$Menu$Item, {
                          icon: React.createElement(ReactFeather.Calendar, {
                                size: "14",
                                className: "mr-3"
                              }),
                          text: "Kalendarz",
                          active: /* Calendar */0 === Router$Peaky.toView(url.path),
                          view: /* Calendar */0
                        }), React.createElement(Layout$Menu$Item, {
                          icon: React.createElement(ReactFeather.User, {
                                size: "14",
                                className: "mr-3"
                              }),
                          text: "Pacjenci",
                          active: tmp,
                          view: /* Patients */1
                        }), React.createElement(Layout$Menu$Item, {
                          icon: React.createElement(ReactFeather.List, {
                                size: "14",
                                className: "mr-3"
                              }),
                          text: "Historia",
                          active: /* Visits */3 === Router$Peaky.toView(url.path),
                          view: /* Visits */3
                        }), React.createElement(Layout$Menu$Item, {
                          icon: React.createElement(ReactFeather.Share2, {
                                size: "14",
                                className: "mr-3"
                              }),
                          text: "Konsultacje",
                          active: tmp$1,
                          view: /* Consultations */2
                        }))), React.createElement("div", {
                  className: "flex px-2 py-4 items-center justify-center flex-col"
                }, React.createElement(Avatar$Peaky.make, tmp$2), React.createElement("div", {
                      className: "h-4"
                    }), React.createElement(Button$Peaky.make, {
                      children: React.createElement(Text$Peaky.make, {
                            children: "Wyloguj się"
                          }),
                      icon: React.createElement(ReactFeather.ArrowRight, {
                            size: "18"
                          }),
                      onClick: (function (param) {
                          return Auth$Peaky.signOut(undefined);
                        })
                    })));
}

var Menu = {
  Item: Item,
  make: Layout$Menu
};

var Raw = {};

var query = Client.gql("query IncomingsConsultations  {\nme  {\n__typename  \nid  \nfirstName  \nlastName  \n}\n\nconsultations  {\n__typename  \nid  \nuserIds  \ncallerId  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.me;
  var value$2 = value.consultations;
  return {
          me: {
            __typename: value$1.__typename,
            id: value$1.id,
            firstName: value$1.firstName,
            lastName: value$1.lastName
          },
          consultations: value$2.map(function (value) {
                var value$1 = value.userIds;
                return {
                        __typename: value.__typename,
                        id: value.id,
                        userIds: value$1.map(function (value) {
                              return value;
                            }),
                        callerId: value.callerId
                      };
              })
        };
}

function serialize(value) {
  var value$1 = value.consultations;
  var consultations = value$1.map(function (value) {
        var value$1 = value.callerId;
        var value$2 = value.userIds;
        var userIds = value$2.map(function (value) {
              return value;
            });
        var value$3 = value.id;
        var value$4 = value.__typename;
        return {
                __typename: value$4,
                id: value$3,
                userIds: userIds,
                callerId: value$1
              };
      });
  var value$2 = value.me;
  var value$3 = value$2.lastName;
  var value$4 = value$2.firstName;
  var value$5 = value$2.id;
  var value$6 = value$2.__typename;
  var me = {
    __typename: value$6,
    id: value$5,
    firstName: value$4,
    lastName: value$3
  };
  return {
          me: me,
          consultations: consultations
        };
}

function serializeVariables(param) {
  
}

function makeVariables(param) {
  
}

function makeDefaultVariables(param) {
  
}

var Query_inner = {
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  makeDefaultVariables: makeDefaultVariables
};

var include = ApolloClient__React_Hooks_UseQuery.Extend({
      query: query,
      Raw: Raw,
      parse: parse,
      serialize: serialize,
      serializeVariables: serializeVariables
    });

var use = include.use;

var Query_refetchQueryDescription = include.refetchQueryDescription;

var Query_useLazy = include.useLazy;

var Query_useLazyWithVariables = include.useLazyWithVariables;

var Query = {
  Query_inner: Query_inner,
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  makeDefaultVariables: makeDefaultVariables,
  refetchQueryDescription: Query_refetchQueryDescription,
  use: use,
  useLazy: Query_useLazy,
  useLazyWithVariables: Query_useLazyWithVariables
};

var Raw$1 = {};

var query$1 = Client.gql("mutation Decline($id: String!, $callerId: String!, $userIds: [String!]!)  {\ndecline(id: $id, callerId: $callerId, userIds: $userIds)  {\n__typename  \nid  \n}\n\n}\n");

function parse$1(value) {
  var value$1 = value.decline;
  return {
          decline: !(value$1 == null) ? ({
                __typename: value$1.__typename,
                id: value$1.id
              }) : undefined
        };
}

function serialize$1(value) {
  var value$1 = value.decline;
  var decline;
  if (value$1 !== undefined) {
    var value$2 = value$1.id;
    var value$3 = value$1.__typename;
    decline = {
      __typename: value$3,
      id: value$2
    };
  } else {
    decline = null;
  }
  return {
          decline: decline
        };
}

function serializeVariables$1(inp) {
  var a = inp.userIds;
  return {
          id: inp.id,
          callerId: inp.callerId,
          userIds: a.map(function (b) {
                return b;
              })
        };
}

function makeVariables$1(id, callerId, userIds, param) {
  return {
          id: id,
          callerId: callerId,
          userIds: userIds
        };
}

var Decline_inner = {
  Raw: Raw$1,
  query: query$1,
  parse: parse$1,
  serialize: serialize$1,
  serializeVariables: serializeVariables$1,
  makeVariables: makeVariables$1
};

var include$1 = ApolloClient__React_Hooks_UseMutation.Extend({
      query: query$1,
      Raw: Raw$1,
      parse: parse$1,
      serialize: serialize$1,
      serializeVariables: serializeVariables$1
    });

var Decline_use = include$1.use;

var Decline_useWithVariables = include$1.useWithVariables;

var Decline = {
  Decline_inner: Decline_inner,
  Raw: Raw$1,
  query: query$1,
  parse: parse$1,
  serialize: serialize$1,
  serializeVariables: serializeVariables$1,
  makeVariables: makeVariables$1,
  use: Decline_use,
  useWithVariables: Decline_useWithVariables
};

function Layout(Props) {
  var children = Props.children;
  var consultations = Curry.app(use, [
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        2000,
        undefined,
        undefined,
        undefined
      ]);
  var match = React.useState(function () {
        
      });
  var setIncomingCall = match[1];
  var incomingCall = match[0];
  var url = ReasonReactRouter.useUrl(undefined, undefined);
  var match$1 = React.useState(function () {
        return true;
      });
  var setOpen = match$1[1];
  React.useEffect((function () {
          var match = consultations.data;
          if (match !== undefined) {
            var me = match.me;
            var incoming = Belt_Array.get(Belt_Array.keep(Belt_Array.reverse(match.consultations), (function (c) {
                        return Belt_Option.isSome(Caml_option.undefined_to_opt(c.userIds.find(function (x) {
                                            return x === me.id;
                                          })));
                      })), 0);
            Curry._1(setIncomingCall, (function (param) {
                    return incoming;
                  }));
          }
          
        }), [consultations]);
  var firstName = Belt_Option.map(consultations.data, (function (c) {
          return c.me.firstName;
        }));
  var lastName = Belt_Option.map(consultations.data, (function (c) {
          return c.me.lastName;
        }));
  var match$2 = url.path;
  return React.createElement("div", {
              className: "flex"
            }, React.createElement(Layout$Menu, {
                  firstName: firstName,
                  lastName: lastName
                }), React.createElement("div", {
                  className: "bg-white flex-1 pl-40"
                }, children), incomingCall !== undefined && match$1[0] && Caml_obj.caml_notequal(Belt_List.get(match$2, 0), "consultations") ? React.createElement("div", undefined, React.createElement("div", {
                        className: "fixed bottom-12 right-12 flex p-8 shadow-lg border border-gray flex-col bg-white rounded-xl"
                      }, React.createElement("span", {
                            className: "text-3xl text-gray-500 mb-8"
                          }, React.createElement(Text$Peaky.make, {
                                children: "Przychodzące połączenie"
                              })), React.createElement("div", {
                            className: "flex justify-around gap-8"
                          }, React.createElement("div", {
                                className: " animate-pulse flex justify-center flex-col items-center w-24 h-24 rounded-full bg-green-500 hover:bg-green-400 cursor-pointer text-white ",
                                onClick: (function (param) {
                                    return Router$Peaky.push({
                                                TAG: /* ConsultationRoom */3,
                                                _0: incomingCall.id
                                              });
                                  })
                              }, React.createElement(ReactFeather.Phone, {
                                    size: "24"
                                  }), React.createElement(Text$Peaky.make, {
                                    children: "Odbierz"
                                  })), React.createElement("div", {
                                className: "flex justify-center flex-col items-center w-24 h-24 rounded-full bg-red-500 hover:bg-red-400 cursor-pointer text-white ",
                                onClick: (function (param) {
                                    return Curry._1(setOpen, (function (param) {
                                                  return false;
                                                }));
                                  })
                              }, React.createElement(ReactFeather.PhoneOff, {}), React.createElement(Text$Peaky.make, {
                                    children: "Odrzuć"
                                  }))))) : null);
}

var make = Layout;

export {
  Menu ,
  Query ,
  Decline ,
  make ,
  
}
/* query Not a pure module */
