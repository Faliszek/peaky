

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

var Raw = {};

var query = Client.gql("mutation AddSyptom($patientId: String!, $name: String!, $date: String!, $circumstances: String!, $description: String!, $occurences: String!, $causedBy: String!, $notes: String!, $color: String!)  {\naddSymptom(patientId: $patientId, name: $name, date: $date, circumstances: $circumstances, description: $description, occurences: $occurences, causedBy: $causedBy, notes: $notes, color: $color)  {\n__typename  \nid  \nname  \ndate  \ncircumstances  \ndescription  \noccurences  \ncausedBy  \nnotes  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.addSymptom;
  return {
          addSymptom: {
            __typename: value$1.__typename,
            id: value$1.id,
            name: value$1.name,
            date: value$1.date,
            circumstances: value$1.circumstances,
            description: value$1.description,
            occurences: value$1.occurences,
            causedBy: value$1.causedBy,
            notes: value$1.notes
          }
        };
}

function serialize(value) {
  var value$1 = value.addSymptom;
  var value$2 = value$1.notes;
  var value$3 = value$1.causedBy;
  var value$4 = value$1.occurences;
  var value$5 = value$1.description;
  var value$6 = value$1.circumstances;
  var value$7 = value$1.date;
  var value$8 = value$1.name;
  var value$9 = value$1.id;
  var value$10 = value$1.__typename;
  var addSymptom = {
    __typename: value$10,
    id: value$9,
    name: value$8,
    date: value$7,
    circumstances: value$6,
    description: value$5,
    occurences: value$4,
    causedBy: value$3,
    notes: value$2
  };
  return {
          addSymptom: addSymptom
        };
}

function serializeVariables(inp) {
  return {
          patientId: inp.patientId,
          name: inp.name,
          date: inp.date,
          circumstances: inp.circumstances,
          description: inp.description,
          occurences: inp.occurences,
          causedBy: inp.causedBy,
          notes: inp.notes,
          color: inp.color
        };
}

function makeVariables(patientId, name, date, circumstances, description, occurences, causedBy, notes, color, param) {
  return {
          patientId: patientId,
          name: name,
          date: date,
          circumstances: circumstances,
          description: description,
          occurences: occurences,
          causedBy: causedBy,
          notes: notes,
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
