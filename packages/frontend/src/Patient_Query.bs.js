

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";

var Raw = {};

var query = Client.gql("query Patient($id: String!)  {\npatient(id: $id)  {\n__typename  \nid  \nfirstName  \nlastName  \nphoneNumber  \ndisease  \nlastVisit  \ncolor  \n}\n\ncalls  {\n__typename  \nid  \nduration  \ntimestamp  \nanswered  \nto_  {\n__typename  \nfirstName  \nlastName  \n}\n\n}\n\nsymptoms(patientId: $id)  {\n__typename  \nid  \nname  \ndate  \ncircumstances  \ndescription  \noccurences  \ncausedBy  \nnotes  \ncolor  \n}\n\npatientEvents(patientId: $id)  {\n__typename  \nid  \nsymptompId  \nfeeling  \ntimestamp  \n}\n\nfeelings(patientId: $id)  {\n__typename  \nid  \npatientId  \nvalue  \ntimestamp  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.patient;
  var value$2 = value$1.lastVisit;
  var value$3 = value.calls;
  var value$4 = value.symptoms;
  var value$5 = value.patientEvents;
  var value$6 = value.feelings;
  return {
          patient: {
            __typename: value$1.__typename,
            id: value$1.id,
            firstName: value$1.firstName,
            lastName: value$1.lastName,
            phoneNumber: value$1.phoneNumber,
            disease: value$1.disease,
            lastVisit: !(value$2 == null) ? value$2 : undefined,
            color: value$1.color
          },
          calls: value$3.map(function (value) {
                var value$1 = value.to_;
                return {
                        __typename: value.__typename,
                        id: value.id,
                        duration: value.duration,
                        timestamp: value.timestamp,
                        answered: value.answered,
                        to_: {
                          __typename: value$1.__typename,
                          firstName: value$1.firstName,
                          lastName: value$1.lastName
                        }
                      };
              }),
          symptoms: value$4.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        name: value.name,
                        date: value.date,
                        circumstances: value.circumstances,
                        description: value.description,
                        occurences: value.occurences,
                        causedBy: value.causedBy,
                        notes: value.notes,
                        color: value.color
                      };
              }),
          patientEvents: value$5.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        symptompId: value.symptompId,
                        feeling: value.feeling,
                        timestamp: value.timestamp
                      };
              }),
          feelings: value$6.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        patientId: value.patientId,
                        value: value.value,
                        timestamp: value.timestamp
                      };
              })
        };
}

function serialize(value) {
  var value$1 = value.feelings;
  var feelings = value$1.map(function (value) {
        var value$1 = value.timestamp;
        var value$2 = value.value;
        var value$3 = value.patientId;
        var value$4 = value.id;
        var value$5 = value.__typename;
        return {
                __typename: value$5,
                id: value$4,
                patientId: value$3,
                value: value$2,
                timestamp: value$1
              };
      });
  var value$2 = value.patientEvents;
  var patientEvents = value$2.map(function (value) {
        var value$1 = value.timestamp;
        var value$2 = value.feeling;
        var value$3 = value.symptompId;
        var value$4 = value.id;
        var value$5 = value.__typename;
        return {
                __typename: value$5,
                id: value$4,
                symptompId: value$3,
                feeling: value$2,
                timestamp: value$1
              };
      });
  var value$3 = value.symptoms;
  var symptoms = value$3.map(function (value) {
        var value$1 = value.color;
        var value$2 = value.notes;
        var value$3 = value.causedBy;
        var value$4 = value.occurences;
        var value$5 = value.description;
        var value$6 = value.circumstances;
        var value$7 = value.date;
        var value$8 = value.name;
        var value$9 = value.id;
        var value$10 = value.__typename;
        return {
                __typename: value$10,
                id: value$9,
                name: value$8,
                date: value$7,
                circumstances: value$6,
                description: value$5,
                occurences: value$4,
                causedBy: value$3,
                notes: value$2,
                color: value$1
              };
      });
  var value$4 = value.calls;
  var calls = value$4.map(function (value) {
        var value$1 = value.to_;
        var value$2 = value$1.lastName;
        var value$3 = value$1.firstName;
        var value$4 = value$1.__typename;
        var to_ = {
          __typename: value$4,
          firstName: value$3,
          lastName: value$2
        };
        var value$5 = value.answered;
        var value$6 = value.timestamp;
        var value$7 = value.duration;
        var value$8 = value.id;
        var value$9 = value.__typename;
        return {
                __typename: value$9,
                id: value$8,
                duration: value$7,
                timestamp: value$6,
                answered: value$5,
                to_: to_
              };
      });
  var value$5 = value.patient;
  var value$6 = value$5.color;
  var value$7 = value$5.lastVisit;
  var lastVisit = value$7 !== undefined ? value$7 : null;
  var value$8 = value$5.disease;
  var value$9 = value$5.phoneNumber;
  var value$10 = value$5.lastName;
  var value$11 = value$5.firstName;
  var value$12 = value$5.id;
  var value$13 = value$5.__typename;
  var patient = {
    __typename: value$13,
    id: value$12,
    firstName: value$11,
    lastName: value$10,
    phoneNumber: value$9,
    disease: value$8,
    lastVisit: lastVisit,
    color: value$6
  };
  return {
          patient: patient,
          calls: calls,
          symptoms: symptoms,
          patientEvents: patientEvents,
          feelings: feelings
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
  refetchQueryDescription: Query_refetchQueryDescription,
  use: Query_use,
  useLazy: Query_useLazy,
  useLazyWithVariables: Query_useLazyWithVariables
};

export {
  Query ,
  
}
/* query Not a pure module */
