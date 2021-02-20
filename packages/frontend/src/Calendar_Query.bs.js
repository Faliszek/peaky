

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";

var Raw = {};

var query = Client.gql("query Visits  {\nvisits  {\n__typename  \nid  \nfrom_  \nto_  \npatientId  \n}\n\npatients  {\n__typename  \nid  \nfirstName  \nlastName  \ndisease  \ncolor  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.visits;
  var value$2 = value.patients;
  return {
          visits: value$1.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        from_: value.from_,
                        to_: value.to_,
                        patientId: value.patientId
                      };
              }),
          patients: value$2.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        firstName: value.firstName,
                        lastName: value.lastName,
                        disease: value.disease,
                        color: value.color
                      };
              })
        };
}

function serialize(value) {
  var value$1 = value.patients;
  var patients = value$1.map(function (value) {
        var value$1 = value.color;
        var value$2 = value.disease;
        var value$3 = value.lastName;
        var value$4 = value.firstName;
        var value$5 = value.id;
        var value$6 = value.__typename;
        return {
                __typename: value$6,
                id: value$5,
                firstName: value$4,
                lastName: value$3,
                disease: value$2,
                color: value$1
              };
      });
  var value$2 = value.visits;
  var visits = value$2.map(function (value) {
        var value$1 = value.patientId;
        var value$2 = value.to_;
        var value$3 = value.from_;
        var value$4 = value.id;
        var value$5 = value.__typename;
        return {
                __typename: value$5,
                id: value$4,
                from_: value$3,
                to_: value$2,
                patientId: value$1
              };
      });
  return {
          visits: visits,
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
