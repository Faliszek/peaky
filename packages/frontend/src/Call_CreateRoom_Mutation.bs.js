

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

var Raw = {};

var query = Client.gql("mutation CreateRoom($patientId: String!, $doctorId: String!)  {\ncreateRoom(patientId: $patientId, doctorId: $doctorId)  {\n__typename  \nid  \ndoctorId  \npatientId  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.createRoom;
  return {
          createRoom: !(value$1 == null) ? ({
                __typename: value$1.__typename,
                id: value$1.id,
                doctorId: value$1.doctorId,
                patientId: value$1.patientId
              }) : undefined
        };
}

function serialize(value) {
  var value$1 = value.createRoom;
  var createRoom;
  if (value$1 !== undefined) {
    var value$2 = value$1.patientId;
    var value$3 = value$1.doctorId;
    var value$4 = value$1.id;
    var value$5 = value$1.__typename;
    createRoom = {
      __typename: value$5,
      id: value$4,
      doctorId: value$3,
      patientId: value$2
    };
  } else {
    createRoom = null;
  }
  return {
          createRoom: createRoom
        };
}

function serializeVariables(inp) {
  return {
          patientId: inp.patientId,
          doctorId: inp.doctorId
        };
}

function makeVariables(patientId, doctorId, param) {
  return {
          patientId: patientId,
          doctorId: doctorId
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
