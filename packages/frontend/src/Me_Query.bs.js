

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";

var Raw = {};

var query = Client.gql("query Me  {\nme  {\n__typename  \nid  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.me;
  return {
          me: {
            __typename: value$1.__typename,
            id: value$1.id
          }
        };
}

function serialize(value) {
  var value$1 = value.me;
  var value$2 = value$1.id;
  var value$3 = value$1.__typename;
  var me = {
    __typename: value$3,
    id: value$2
  };
  return {
          me: me
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
