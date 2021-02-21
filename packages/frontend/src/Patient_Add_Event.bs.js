

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "@rescript/std/lib/es6/belt_Array.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Caml_format from "@rescript/std/lib/es6/caml_format.js";
import * as Input$Peaky from "./components/Input.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Select$Peaky from "./components/Select.bs.js";
import * as ReactFeather from "react-feather";
import * as Client from "@apollo/client";
import * as Patient_Query$Peaky from "./Patient_Query.bs.js";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

var Raw = {};

var query = Client.gql("query Patient($id: String!)  {\nsymptoms(patientId: $id)  {\n__typename  \nid  \nname  \ndate  \ncircumstances  \ndescription  \noccurences  \ncausedBy  \nnotes  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.symptoms;
  return {
          symptoms: value$1.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        name: value.name,
                        date: value.date,
                        circumstances: value.circumstances,
                        description: value.description,
                        occurences: value.occurences,
                        causedBy: value.causedBy,
                        notes: value.notes
                      };
              })
        };
}

function serialize(value) {
  var value$1 = value.symptoms;
  var symptoms = value$1.map(function (value) {
        var value$1 = value.notes;
        var value$2 = value.causedBy;
        var value$3 = value.occurences;
        var value$4 = value.description;
        var value$5 = value.circumstances;
        var value$6 = value.date;
        var value$7 = value.name;
        var value$8 = value.id;
        var value$9 = value.__typename;
        return {
                __typename: value$9,
                id: value$8,
                name: value$7,
                date: value$6,
                circumstances: value$5,
                description: value$4,
                occurences: value$3,
                causedBy: value$2,
                notes: value$1
              };
      });
  return {
          symptoms: symptoms
        };
}

function serializeVariables(inp) {
  return {
          id: inp.id
        };
}

function makeVariables(id, param) {
  return {
          id: id
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

var refetchQueryDescription = include.refetchQueryDescription;

var useLazy = include.useLazy;

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
  refetchQueryDescription: refetchQueryDescription,
  use: Query_use,
  useLazy: useLazy,
  useLazyWithVariables: Query_useLazyWithVariables
};

var Raw$1 = {};

var query$1 = Client.gql("mutation AddFeeling($patientId: String!, $value: String!, $timestamp: Float!)  {\naddFeeling(patientId: $patientId, value: $value, timestamp: $timestamp)  {\n__typename  \nid  \npatientId  \nvalue  \ntimestamp  \n}\n\n}\n");

function parse$1(value) {
  var value$1 = value.addFeeling;
  return {
          addFeeling: {
            __typename: value$1.__typename,
            id: value$1.id,
            patientId: value$1.patientId,
            value: value$1.value,
            timestamp: value$1.timestamp
          }
        };
}

function serialize$1(value) {
  var value$1 = value.addFeeling;
  var value$2 = value$1.timestamp;
  var value$3 = value$1.value;
  var value$4 = value$1.patientId;
  var value$5 = value$1.id;
  var value$6 = value$1.__typename;
  var addFeeling = {
    __typename: value$6,
    id: value$5,
    patientId: value$4,
    value: value$3,
    timestamp: value$2
  };
  return {
          addFeeling: addFeeling
        };
}

function serializeVariables$1(inp) {
  return {
          patientId: inp.patientId,
          value: inp.value,
          timestamp: inp.timestamp
        };
}

function makeVariables$1(patientId, value, timestamp, param) {
  return {
          patientId: patientId,
          value: value,
          timestamp: timestamp
        };
}

var AddFeeling_inner = {
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

var AddFeeling_useWithVariables = include$1.useWithVariables;

var AddFeeling = {
  AddFeeling_inner: AddFeeling_inner,
  Raw: Raw$1,
  query: query$1,
  parse: parse$1,
  serialize: serialize$1,
  serializeVariables: serializeVariables$1,
  makeVariables: makeVariables$1,
  use: use,
  useWithVariables: AddFeeling_useWithVariables
};

var Raw$2 = {};

var query$2 = Client.gql("mutation AddEventMutation($patientId: String!, $symptomId: String!, $feeling: Float!, $timestamp: Float!)  {\naddPatientEvent(patientId: $patientId, symptompId: $symptomId, feeling: $feeling, timestamp: $timestamp)  {\n__typename  \nid  \nsymptompId  \nfeeling  \ntimestamp  \n}\n\n}\n");

function parse$2(value) {
  var value$1 = value.addPatientEvent;
  return {
          addPatientEvent: {
            __typename: value$1.__typename,
            id: value$1.id,
            symptompId: value$1.symptompId,
            feeling: value$1.feeling,
            timestamp: value$1.timestamp
          }
        };
}

function serialize$2(value) {
  var value$1 = value.addPatientEvent;
  var value$2 = value$1.timestamp;
  var value$3 = value$1.feeling;
  var value$4 = value$1.symptompId;
  var value$5 = value$1.id;
  var value$6 = value$1.__typename;
  var addPatientEvent = {
    __typename: value$6,
    id: value$5,
    symptompId: value$4,
    feeling: value$3,
    timestamp: value$2
  };
  return {
          addPatientEvent: addPatientEvent
        };
}

function serializeVariables$2(inp) {
  return {
          patientId: inp.patientId,
          symptomId: inp.symptomId,
          feeling: inp.feeling,
          timestamp: inp.timestamp
        };
}

function makeVariables$2(patientId, symptomId, feeling, timestamp, param) {
  return {
          patientId: patientId,
          symptomId: symptomId,
          feeling: feeling,
          timestamp: timestamp
        };
}

var AddEventMutation_inner = {
  Raw: Raw$2,
  query: query$2,
  parse: parse$2,
  serialize: serialize$2,
  serializeVariables: serializeVariables$2,
  makeVariables: makeVariables$2
};

var include$2 = ApolloClient__React_Hooks_UseMutation.Extend({
      query: query$2,
      Raw: Raw$2,
      parse: parse$2,
      serialize: serialize$2,
      serializeVariables: serializeVariables$2
    });

var use$1 = include$2.use;

var AddEventMutation_useWithVariables = include$2.useWithVariables;

var AddEventMutation = {
  AddEventMutation_inner: AddEventMutation_inner,
  Raw: Raw$2,
  query: query$2,
  parse: parse$2,
  serialize: serialize$2,
  serializeVariables: serializeVariables$2,
  makeVariables: makeVariables$2,
  use: use$1,
  useWithVariables: AddEventMutation_useWithVariables
};

function Patient_Add_Event$AddEvent(Props) {
  var onClose = Props.onClose;
  var patientId = Props.patientId;
  var symptom = Select$Peaky.use(undefined);
  var match = React.useState(function () {
        return {
                strength: "",
                notes: ""
              };
      });
  var setValues = match[1];
  var values = match[0];
  var match$1 = React.useState(function () {
        return "";
      });
  var setFeeling = match$1[1];
  var feeling = match$1[0];
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
  var query = match$2[0];
  React.useEffect((function () {
          if (patientId !== undefined) {
            Curry._3(query, undefined, undefined, {
                  id: patientId
                });
          }
          
        }), [patientId]);
  var symptoms;
  if (result.TAG === /* Executed */0) {
    var match$3 = result._0.data;
    symptoms = match$3 !== undefined ? Belt_Array.map(match$3.symptoms, (function (s) {
              return {
                      value: s.id,
                      label: s.name
                    };
            })) : [];
  } else {
    symptoms = [];
  }
  var match$4 = Curry.app(use$1, [
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
  var addEvent = match$4[0];
  var match$5 = Curry.app(use, [
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
  var addFeeling = match$5[0];
  var tmp;
  tmp = result.TAG === /* Executed */0 && result._0.loading ? true : false;
  return React.createElement("div", {
              className: "w-64 bg-white shadow-xl rounded-xl fixed top-12 right-12 py-8 px-6 border border-gray-200",
              style: {
                width: "450px"
              }
            }, React.createElement("div", {
                  className: "text-2xl text-gray-600 mb-4 flex justify-between"
                }, React.createElement(Text$Peaky.make, {
                      children: "Zaktualizuj przebieg choroby"
                    }), React.createElement(Button$Peaky.Nav.make, {
                      onClick: (function (param) {
                          return Curry._1(onClose, undefined);
                        }),
                      children: React.createElement(ReactFeather.Plus, {
                            size: "18",
                            className: "transform rotate-45"
                          })
                    })), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Select$Peaky.make, {
                        value: symptom.value,
                        search: symptom.search,
                        onSearchChange: symptom.setSearch,
                        placeholder: "Wybierz symptom",
                        icon: React.createElement(ReactFeather.Thermometer, {}),
                        visible: symptom.visible,
                        onVisibleChange: symptom.setVisible,
                        options: symptoms,
                        onChange: symptom.setValue,
                        loading: tmp
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: values.strength,
                        onChange: (function (strength) {
                            return Curry._1(setValues, (function (values) {
                                          return {
                                                  strength: strength,
                                                  notes: values.notes
                                                };
                                        }));
                          }),
                        placeholder: "Siła objawu"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.Textarea.make, {
                        placeholder: "Dodatkowe informacje",
                        value: values.notes,
                        onChange: (function (notes) {
                            return Curry._1(setValues, (function (values) {
                                          return {
                                                  strength: values.strength,
                                                  notes: notes
                                                };
                                        }));
                          })
                      })
                }), React.createElement("div", {
                  className: "flex justify-end"
                }, React.createElement(Button$Peaky.CTA.make, {
                      loading: match$4[1].loading,
                      children: React.createElement(Text$Peaky.make, {
                            children: "Dodaj informację"
                          }),
                      onClick: (function (param) {
                          var match = symptom.value;
                          if (patientId !== undefined && match !== undefined) {
                            Curry._8(addEvent, undefined, undefined, undefined, undefined, undefined, [
                                  Curry._3(Patient_Query$Peaky.Query.refetchQueryDescription, undefined, undefined, {
                                        id: patientId
                                      }),
                                  Curry._3(refetchQueryDescription, undefined, undefined, {
                                        id: patientId
                                      })
                                ], undefined, {
                                  patientId: patientId,
                                  symptomId: match.value,
                                  feeling: Caml_format.caml_float_of_string(values.strength),
                                  timestamp: Date.now()
                                });
                            return ;
                          }
                          
                        })
                    })), React.createElement("div", {
                  className: "text-2xl text-gray-600 mb-4 mt-8"
                }, React.createElement(Text$Peaky.make, {
                      children: "Samopoczucie"
                    })), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: feeling,
                        onChange: (function (v) {
                            return Curry._1(setFeeling, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Samopoczucie"
                      })
                }), React.createElement("div", {
                  className: "flex justify-end"
                }, React.createElement(Button$Peaky.CTA.make, {
                      loading: match$5[1].loading,
                      children: React.createElement(Text$Peaky.make, {
                            children: "Zapisz"
                          }),
                      onClick: (function (param) {
                          if (patientId !== undefined) {
                            Curry._8(addFeeling, undefined, undefined, undefined, undefined, undefined, [
                                  Curry._3(Patient_Query$Peaky.Query.refetchQueryDescription, undefined, undefined, {
                                        id: patientId
                                      }),
                                  Curry._3(refetchQueryDescription, undefined, undefined, {
                                        id: patientId
                                      })
                                ], undefined, {
                                  patientId: patientId,
                                  value: feeling,
                                  timestamp: Date.now()
                                });
                            return ;
                          }
                          
                        })
                    })));
}

var AddEvent = {
  make: Patient_Add_Event$AddEvent
};

function Patient_Add_Event(Props) {
  var patientId = Props.patientId;
  var match = React.useState(function () {
        return false;
      });
  var setVisible = match[1];
  var visible = match[0];
  return React.createElement("div", {
              className: "fixed bottom-12 right-12"
            }, visible ? React.createElement(Patient_Add_Event$AddEvent, {
                    onClose: (function (param) {
                        return Curry._1(setVisible, (function (param) {
                                      return false;
                                    }));
                      }),
                    patientId: patientId
                  }) : null, React.createElement(Button$Peaky.SmallRound.make, {
                  icon: React.createElement(ReactFeather.Plus, {
                        size: "32"
                      }),
                  onClick: (function (param) {
                      return Curry._1(setVisible, (function (x) {
                                    return !x;
                                  }));
                    }),
                  className: Cn.$plus("w-16 h-16 transform transition-transform", Cn.on("rotate-45", visible))
                }));
}

var make = Patient_Add_Event;

export {
  Query ,
  AddFeeling ,
  AddEventMutation ,
  AddEvent ,
  make ,
  
}
/* query Not a pure module */
