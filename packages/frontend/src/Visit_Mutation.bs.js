

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

var Raw = {};

var query = Client.gql("mutation createVisit($patientId: String!, $from_: String!, $to_: String!, $notes: String)  {\ncreateVisit(patientId: $patientId, from_: $from_, to_: $to_, notes: $notes)  {\n__typename  \nid  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.createVisit;
  return {
          createVisit: !(value$1 == null) ? ({
                __typename: value$1.__typename,
                id: value$1.id
              }) : undefined
        };
}

function serialize(value) {
  var value$1 = value.createVisit;
  var createVisit;
  if (value$1 !== undefined) {
    var value$2 = value$1.id;
    var value$3 = value$1.__typename;
    createVisit = {
      __typename: value$3,
      id: value$2
    };
  } else {
    createVisit = null;
  }
  return {
          createVisit: createVisit
        };
}

function serializeVariables(inp) {
  var a = inp.notes;
  return {
          patientId: inp.patientId,
          from_: inp.from_,
          to_: inp.to_,
          notes: a !== undefined ? a : undefined
        };
}

function makeVariables(patientId, from_, to_, notes, param) {
  return {
          patientId: patientId,
          from_: from_,
          to_: to_,
          notes: notes
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

var Mutation_use = include.use;

var Mutation_useWithVariables = include.useWithVariables;

var Mutation = {
  Mutation_inner: Mutation_inner,
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  use: Mutation_use,
  useWithVariables: Mutation_useWithVariables
};

export {
  Mutation ,
  
}
/* query Not a pure module */
