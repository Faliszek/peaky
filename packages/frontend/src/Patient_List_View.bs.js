

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Page$Peaky from "./components/Page.bs.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as NoData$Peaky from "./components/NoData.bs.js";
import * as Request$Peaky from "./Request.bs.js";
import * as Spinner$Peaky from "./components/Spinner.bs.js";
import * as ReactFeather from "react-feather";
import * as Client from "@apollo/client";
import * as Patient_Block$Peaky from "./Patient_Block.bs.js";
import * as Patient_AddPatient$Peaky from "./Patient_AddPatient.bs.js";
import * as Patient_List_Query$Peaky from "./Patient_List_Query.bs.js";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

var Raw = {};

var query = Client.gql("mutation CreatePatient($firstName: String!, $lastName: String!, $phoneNumber: String!, $disease: String!, $color: String!)  {\ncreatePatient(firstName: $firstName, lastName: $lastName, phoneNumber: $phoneNumber, disease: $disease, color: $color)  {\n__typename  \nid  \nfirstName  \nlastName  \nphoneNumber  \ndisease  \ncolor  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.createPatient;
  return {
          createPatient: {
            __typename: value$1.__typename,
            id: value$1.id,
            firstName: value$1.firstName,
            lastName: value$1.lastName,
            phoneNumber: value$1.phoneNumber,
            disease: value$1.disease,
            color: value$1.color
          }
        };
}

function serialize(value) {
  var value$1 = value.createPatient;
  var value$2 = value$1.color;
  var value$3 = value$1.disease;
  var value$4 = value$1.phoneNumber;
  var value$5 = value$1.lastName;
  var value$6 = value$1.firstName;
  var value$7 = value$1.id;
  var value$8 = value$1.__typename;
  var createPatient = {
    __typename: value$8,
    id: value$7,
    firstName: value$6,
    lastName: value$5,
    phoneNumber: value$4,
    disease: value$3,
    color: value$2
  };
  return {
          createPatient: createPatient
        };
}

function serializeVariables(inp) {
  return {
          firstName: inp.firstName,
          lastName: inp.lastName,
          phoneNumber: inp.phoneNumber,
          disease: inp.disease,
          color: inp.color
        };
}

function makeVariables(firstName, lastName, phoneNumber, disease, color, param) {
  return {
          firstName: firstName,
          lastName: lastName,
          phoneNumber: phoneNumber,
          disease: disease,
          color: color
        };
}

var Mutation_inner = {
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables
};

var include = ApolloClient__React_Hooks_UseMutation.Extend({
      query: query,
      Raw: Raw,
      parse: parse,
      serialize: serialize,
      serializeVariables: serializeVariables
    });

var use = include.use;

var Mutation_useWithVariables = include.useWithVariables;

var Mutation = {
  Mutation_inner: Mutation_inner,
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  use: use,
  useWithVariables: Mutation_useWithVariables
};

function Patient_List_View(Props) {
  var $staropt$star = Props.callMode;
  if ($staropt$star === undefined) {
    false;
  }
  var match = React.useState(function () {
        return false;
      });
  var setCreatorVisible = match[1];
  var queryUsers = Curry.app(Patient_List_Query$Peaky.Query.use, [
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
        undefined,
        undefined
      ]);
  var match$1 = Curry.app(use, [
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
        [Curry._3(Patient_List_Query$Peaky.Query.refetchQueryDescription, undefined, undefined, undefined)],
        undefined,
        undefined
      ]);
  var createUser = match$1[0];
  var data = queryUsers.data;
  return React.createElement(Page$Peaky.make, {
              title: "Pacjenci",
              children: null,
              actions: React.createElement(Button$Peaky.CTA.make, {
                    children: React.createElement(Text$Peaky.make, {
                          children: "Dodaj pacjenta"
                        }),
                    icon: React.createElement(ReactFeather.Plus, {
                          className: "mr-4"
                        }),
                    onClick: (function (param) {
                        return Curry._1(setCreatorVisible, (function (param) {
                                      return true;
                                    }));
                      })
                  })
            }, React.createElement("div", undefined, queryUsers.loading ? React.createElement(Spinner$Peaky.make, {}) : (
                    data !== undefined ? (
                        data.patients.length === 0 ? React.createElement(NoData$Peaky.make, {
                                buttonText: "Dodaj pacjenta",
                                buttonIcon: React.createElement(ReactFeather.Plus, {}),
                                onButtonClick: (function (param) {
                                    return Curry._1(setCreatorVisible, (function (param) {
                                                  return true;
                                                }));
                                  }),
                                title: "Brak danych",
                                text: "Kliknij przycisk poniżej aby otworzyć kreator pacjenta"
                              }) : React.createElement("div", {
                                className: "flex flex-wrap justify-between items-stretch"
                              }, Belt_Array.map(data.patients, (function (patient) {
                                      return React.createElement(Patient_Block$Peaky.make, {
                                                  patient: patient,
                                                  className: "w-1/3 flex-auto mb-8 mr-12",
                                                  key: patient.id
                                                });
                                    })))
                      ) : null
                  )), React.createElement(Patient_AddPatient$Peaky.make, {
                  visible: match[0],
                  onClose: (function (param) {
                      return Curry._1(setCreatorVisible, (function (param) {
                                    return false;
                                  }));
                    }),
                  onCreate: (function (firstName, lastName, phoneNumber, disease, color) {
                      return Request$Peaky.onFinish(Curry._8(createUser, undefined, undefined, undefined, undefined, undefined, undefined, undefined, {
                                      firstName: firstName,
                                      lastName: lastName,
                                      phoneNumber: phoneNumber,
                                      disease: disease,
                                      color: color
                                    }), (function (param) {
                                    return Curry._1(setCreatorVisible, (function (param) {
                                                  return false;
                                                }));
                                  }), (function (param) {
                                    console.log("unexpected");
                                    
                                  }));
                    }),
                  loading: match$1[1].loading
                }));
}

var ListQuery;

var make = Patient_List_View;

export {
  Mutation ,
  ListQuery ,
  make ,
  
}
/* query Not a pure module */
