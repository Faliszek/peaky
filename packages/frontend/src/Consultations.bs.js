

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Page$Peaky from "./components/Page.bs.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Input$Peaky from "./components/Input.bs.js";
import * as Table$Peaky from "./Table.bs.js";
import * as Avatar$Peaky from "./components/Avatar.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as NoData$Peaky from "./components/NoData.bs.js";
import * as Router$Peaky from "./Router.bs.js";
import * as Select$Peaky from "./components/Select.bs.js";
import * as Request$Peaky from "./Request.bs.js";
import * as Spinner$Peaky from "./components/Spinner.bs.js";
import * as ReactFeather from "react-feather";
import * as Client from "@apollo/client";
import * as Specialization$Peaky from "./Specialization.bs.js";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

function Consultations$SearchComponent(Props) {
  var children = Props.children;
  return React.createElement("div", {
              className: "flex-1 mr-8"
            }, children);
}

var SearchComponent = {
  make: Consultations$SearchComponent
};

var Raw = {};

var query = Client.gql("query Search($specialization: String!, $firstName: String!, $lastName: String!)  {\nme  {\n__typename  \nid  \n}\n\nsearchSpecialist(specialization: $specialization, firstName: $firstName, lastName: $lastName)  {\n__typename  \nid  \nfirstName  \nlastName  \nspecialization  \nonline  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.me;
  var value$2 = value.searchSpecialist;
  return {
          me: {
            __typename: value$1.__typename,
            id: value$1.id
          },
          searchSpecialist: value$2.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        firstName: value.firstName,
                        lastName: value.lastName,
                        specialization: value.specialization,
                        online: value.online
                      };
              })
        };
}

function serialize(value) {
  var value$1 = value.searchSpecialist;
  var searchSpecialist = value$1.map(function (value) {
        var value$1 = value.online;
        var value$2 = value.specialization;
        var value$3 = value.lastName;
        var value$4 = value.firstName;
        var value$5 = value.id;
        var value$6 = value.__typename;
        return {
                __typename: value$6,
                id: value$5,
                firstName: value$4,
                lastName: value$3,
                specialization: value$2,
                online: value$1
              };
      });
  var value$2 = value.me;
  var value$3 = value$2.id;
  var value$4 = value$2.__typename;
  var me = {
    __typename: value$4,
    id: value$3
  };
  return {
          me: me,
          searchSpecialist: searchSpecialist
        };
}

function serializeVariables(inp) {
  return {
          specialization: inp.specialization,
          firstName: inp.firstName,
          lastName: inp.lastName
        };
}

function makeVariables(specialization, firstName, lastName, param) {
  return {
          specialization: specialization,
          firstName: firstName,
          lastName: lastName
        };
}

var Query_inner = {
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables
};

var include = ApolloClient__React_Hooks_UseQuery.Extend({
      query: query,
      Raw: Raw,
      parse: parse,
      serialize: serialize,
      serializeVariables: serializeVariables
    });

var useLazy = include.useLazy;

var Query_refetchQueryDescription = include.refetchQueryDescription;

var Query_use = include.use;

var Query_useLazyWithVariables = include.useLazyWithVariables;

var Query = {
  Query_inner: Query_inner,
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  refetchQueryDescription: Query_refetchQueryDescription,
  use: Query_use,
  useLazy: useLazy,
  useLazyWithVariables: Query_useLazyWithVariables
};

var Raw$1 = {};

var query$1 = Client.gql("mutation Consultation($userIds: [String!]!, $callerId: String!)  {\ncreateConsultation(userIds: $userIds, callerId: $callerId)  {\n__typename  \nid  \ncallerId  \nuserIds  \n}\n\n}\n");

function parse$1(value) {
  var value$1 = value.createConsultation;
  var tmp;
  if (value$1 == null) {
    tmp = undefined;
  } else {
    var value$2 = value$1.userIds;
    tmp = {
      __typename: value$1.__typename,
      id: value$1.id,
      callerId: value$1.callerId,
      userIds: value$2.map(function (value) {
            return value;
          })
    };
  }
  return {
          createConsultation: tmp
        };
}

function serialize$1(value) {
  var value$1 = value.createConsultation;
  var createConsultation;
  if (value$1 !== undefined) {
    var value$2 = value$1.userIds;
    var userIds = value$2.map(function (value) {
          return value;
        });
    var value$3 = value$1.callerId;
    var value$4 = value$1.id;
    var value$5 = value$1.__typename;
    createConsultation = {
      __typename: value$5,
      id: value$4,
      callerId: value$3,
      userIds: userIds
    };
  } else {
    createConsultation = null;
  }
  return {
          createConsultation: createConsultation
        };
}

function serializeVariables$1(inp) {
  var a = inp.userIds;
  return {
          userIds: a.map(function (b) {
                return b;
              }),
          callerId: inp.callerId
        };
}

function makeVariables$1(userIds, callerId, param) {
  return {
          userIds: userIds,
          callerId: callerId
        };
}

var CreateConsultation_inner = {
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

var use = include$1.use;

var CreateConsultation_useWithVariables = include$1.useWithVariables;

var CreateConsultation = {
  CreateConsultation_inner: CreateConsultation_inner,
  Raw: Raw$1,
  query: query$1,
  parse: parse$1,
  serialize: serialize$1,
  serializeVariables: serializeVariables$1,
  makeVariables: makeVariables$1,
  use: use,
  useWithVariables: CreateConsultation_useWithVariables
};

function Consultations$Checkbox(Props) {
  var checked = Props.checked;
  var onChange = Props.onChange;
  var disabled = Props.disabled;
  var bg = checked ? "bg-green-500" : "bg-white border-2 border-gray-400";
  var state = disabled ? "" : "cursor-pointer";
  return React.createElement("div", {
              className: Cn.$plus(Cn.$plus("w-8 h-8 rounded-xl flex items-center justify-center text-white", bg), state),
              onClick: (function (param) {
                  if (!disabled) {
                    return Curry._1(onChange, undefined);
                  }
                  
                })
            }, checked ? React.createElement(ReactFeather.Check, {}) : null);
}

var Checkbox = {
  make: Consultations$Checkbox
};

function Consultations(Props) {
  var specialization = Select$Peaky.use(undefined);
  var match = React.useState(function () {
        return "";
      });
  var setFirstName = match[1];
  var firstName = match[0];
  var match$1 = React.useState(function () {
        return "";
      });
  var setLastName = match$1[1];
  var lastName = match$1[0];
  var match$2 = Curry.app(useLazy, [
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
        undefined,
        undefined
      ]);
  var result = match$2[1];
  var executeQuery = match$2[0];
  var match$3 = React.useState(function () {
        return [];
      });
  var setCheckedIds = match$3[1];
  var checkedIds = match$3[0];
  var ids = checkedIds.length.toString();
  var match$4 = Curry.app(use, [
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
        undefined,
        undefined,
        undefined
      ]);
  var createConsultation = match$4[0];
  var tmp;
  if (result.TAG === /* Executed */0) {
    var match$5 = result._0;
    var match$6 = match$5.data;
    if (match$5.loading) {
      tmp = React.createElement(Spinner$Peaky.make, {});
    } else if (match$6 !== undefined) {
      var me = match$6.me;
      tmp = React.createElement("div", undefined, React.createElement("div", {
                className: "shadow-md border border-gray-200 rounded-lg px-8"
              }, React.createElement("div", {
                    className: "flex w-full"
                  }, React.createElement(Table$Peaky.Th.make, {
                        text: "",
                        width: "w-1/5"
                      }), React.createElement(Table$Peaky.Th.make, {
                        text: "Użytkownik",
                        width: "w-1/4"
                      }), React.createElement(Table$Peaky.Th.make, {
                        text: "Specjalizacja",
                        width: "w-1/4"
                      })), React.createElement("div", {
                    className: "flex w-full flex-col"
                  }, Belt_Array.map(match$6.searchSpecialist, (function (c) {
                          return React.createElement("div", {
                                      key: c.id,
                                      className: "flex w-full border-t border-gray-300 items-center jus"
                                    }, React.createElement(Table$Peaky.Td.make, {
                                          width: "w-1/5",
                                          children: React.createElement(Consultations$Checkbox, {
                                                checked: Belt_Option.isSome(Caml_option.undefined_to_opt(checkedIds.find(function (x) {
                                                              return x === c.id;
                                                            }))),
                                                onChange: (function (param) {
                                                    return Curry._1(setCheckedIds, (function (checked) {
                                                                  if (Belt_Option.isSome(Caml_option.undefined_to_opt(checked.find(function (x) {
                                                                                  return x === c.id;
                                                                                })))) {
                                                                    return Belt_Array.keep(checked, (function (x) {
                                                                                  return x !== c.id;
                                                                                }));
                                                                  } else {
                                                                    return Belt_Array.concat(checked, [c.id]);
                                                                  }
                                                                }));
                                                  }),
                                                disabled: !c.online
                                              })
                                        }), React.createElement(Table$Peaky.Td.make, {
                                          width: "w-1/4",
                                          children: React.createElement("div", {
                                                className: "flex items-center justify-start w-full"
                                              }, React.createElement(Avatar$Peaky.make, {
                                                    firstName: c.firstName,
                                                    lastName: c.lastName
                                                  }), React.createElement("span", {
                                                    className: "ml-4 text-xl"
                                                  }, React.createElement(Text$Peaky.make, {
                                                        children: c.firstName + (" " + c.lastName)
                                                      })))
                                        }), React.createElement(Table$Peaky.Td.make, {
                                          width: "w-1/4",
                                          children: React.createElement(Text$Peaky.make, {
                                                children: c.specialization
                                              })
                                        }));
                        })))), checkedIds.length !== 0 ? React.createElement("div", {
                  className: "fixed right-12 bottom-12"
                }, React.createElement(Button$Peaky.CTA.make, {
                      loading: match$4[1].loading,
                      children: React.createElement(Text$Peaky.make, {
                            children: "Przejdź do konsultacji online (" + ids + ")"
                          }),
                      className: "  animate-pulse",
                      icon: React.createElement(ReactFeather.Video, {
                            className: "mr-4"
                          }),
                      onClick: (function (param) {
                          return Request$Peaky.onFinish(Curry._8(createConsultation, undefined, undefined, undefined, undefined, undefined, undefined, undefined, {
                                          userIds: checkedIds,
                                          callerId: me.id
                                        }), (function (param) {
                                        Belt_Option.map(param.createConsultation, (function (c) {
                                                return Router$Peaky.push({
                                                            TAG: /* ConsultationRoom */3,
                                                            _0: c.id
                                                          });
                                              }));
                                        
                                      }), (function (param) {
                                        
                                      }));
                        })
                    })) : null);
    } else {
      tmp = null;
    }
  } else {
    tmp = React.createElement(NoData$Peaky.make, {
          title: "Wyszukaj specjalistów",
          text: "Wprowadź kryteria wyszukiwania a następnie kliknij przycisk \"Wyszukaj\"",
          icon: React.createElement(ReactFeather.Search, {
                size: "64"
              })
        });
  }
  return React.createElement(Page$Peaky.make, {
              title: "Konsultacje",
              children: null
            }, React.createElement("div", {
                  className: "text-lg p-4 flex items-center border-2 border-blue-100 rounded-lg mb-12 bg-blue-50 text-blue-300"
                }, React.createElement(ReactFeather.Info, {}), React.createElement("span", {
                      className: "ml-4 "
                    }, React.createElement(Text$Peaky.make, {
                          children: "Tutaj możesz znaleźć specjalistów z różnych dziedzin którzy mogą pomóc ci w diagnozie twoich pacjentów"
                        }))), React.createElement("div", {
                  className: "flex justify-items-start"
                }, React.createElement(Consultations$SearchComponent, {
                      children: React.createElement(Select$Peaky.make, {
                            value: specialization.value,
                            search: specialization.search,
                            onSearchChange: specialization.setSearch,
                            placeholder: "Wybierz specjalizację",
                            icon: React.createElement(ReactFeather.Tag, {}),
                            visible: specialization.visible,
                            onVisibleChange: specialization.setVisible,
                            options: Specialization$Peaky.all,
                            onChange: specialization.setValue
                          })
                    }), React.createElement(Consultations$SearchComponent, {
                      children: React.createElement(Input$Peaky.make, {
                            value: firstName,
                            onChange: (function (v) {
                                return Curry._1(setFirstName, (function (param) {
                                              return v;
                                            }));
                              }),
                            placeholder: "Imię"
                          })
                    }), React.createElement(Consultations$SearchComponent, {
                      children: React.createElement(Input$Peaky.make, {
                            value: lastName,
                            onChange: (function (v) {
                                return Curry._1(setLastName, (function (param) {
                                              return v;
                                            }));
                              }),
                            placeholder: "Nazwisko"
                          })
                    }), React.createElement(Button$Peaky.CTA.make, {
                      children: React.createElement("span", {
                            className: "ml-4"
                          }, React.createElement(Text$Peaky.make, {
                                children: "Wyszukaj"
                              })),
                      icon: React.createElement(ReactFeather.Search, {}),
                      onClick: (function (param) {
                          return Curry._3(executeQuery, undefined, undefined, {
                                      specialization: specialization.search,
                                      firstName: firstName,
                                      lastName: lastName
                                    });
                        })
                    })), React.createElement("div", {
                  className: "pt-12"
                }, tmp));
}

var make = Consultations;

export {
  SearchComponent ,
  Query ,
  CreateConsultation ,
  Checkbox ,
  make ,
  
}
/* query Not a pure module */
