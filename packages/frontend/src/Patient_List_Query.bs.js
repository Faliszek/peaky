

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";

var Raw = {};

var query = Client.gql("query Patients  {\npatients  {\n__typename  \nid  \nfirstName  \nlastName  \nphoneNumber  \ndisease  \nlastVisit  \ncolor  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.patients;
  return {
          patients: value$1.map(function (value) {
                var value$1 = value.lastVisit;
                return {
                        __typename: value.__typename,
                        id: value.id,
                        firstName: value.firstName,
                        lastName: value.lastName,
                        phoneNumber: value.phoneNumber,
                        disease: value.disease,
                        lastVisit: !(value$1 == null) ? value$1 : undefined,
                        color: value.color
                      };
              })
        };
}

function serialize(value) {
  var value$1 = value.patients;
  var patients = value$1.map(function (value) {
        var value$1 = value.color;
        var value$2 = value.lastVisit;
        var lastVisit = value$2 !== undefined ? value$2 : null;
        var value$3 = value.disease;
        var value$4 = value.phoneNumber;
        var value$5 = value.lastName;
        var value$6 = value.firstName;
        var value$7 = value.id;
        var value$8 = value.__typename;
        return {
                __typename: value$8,
                id: value$7,
                firstName: value$6,
                lastName: value$5,
                phoneNumber: value$4,
                disease: value$3,
                lastVisit: lastVisit,
                color: value$1
              };
      });
  return {
          patients: patients
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

var Query_refetchQueryDescription = include.refetchQueryDescription;

var Query_use = include.use;

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
  use: Query_use,
  useLazy: Query_useLazy,
  useLazyWithVariables: Query_useLazyWithVariables
};

export {
  Query ,
  
}
/* query Not a pure module */
