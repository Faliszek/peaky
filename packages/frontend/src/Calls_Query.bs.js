

import * as Client from "@apollo/client";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";

var Raw = {};

var query = Client.gql("query Calls  {\nme  {\n__typename  \nid  \n}\n\ncalls  {\n__typename  \nid  \nduration  \ntimestamp  \nanswered  \nfrom_  {\n__typename  \nid  \nfirstName  \nlastName  \n}\n\nto_  {\n__typename  \nid  \nfirstName  \nlastName  \n}\n\n}\n\n}\n");

function parse(value) {
  var value$1 = value.me;
  var value$2 = value.calls;
  return {
          me: {
            __typename: value$1.__typename,
            id: value$1.id
          },
          calls: value$2.map(function (value) {
                var value$1 = value.from_;
                var value$2 = value.to_;
                return {
                        __typename: value.__typename,
                        id: value.id,
                        duration: value.duration,
                        timestamp: value.timestamp,
                        answered: value.answered,
                        from_: {
                          __typename: value$1.__typename,
                          id: value$1.id,
                          firstName: value$1.firstName,
                          lastName: value$1.lastName
                        },
                        to_: {
                          __typename: value$2.__typename,
                          id: value$2.id,
                          firstName: value$2.firstName,
                          lastName: value$2.lastName
                        }
                      };
              })
        };
}

function serialize(value) {
  var value$1 = value.calls;
  var calls = value$1.map(function (value) {
        var value$1 = value.to_;
        var value$2 = value$1.lastName;
        var value$3 = value$1.firstName;
        var value$4 = value$1.id;
        var value$5 = value$1.__typename;
        var to_ = {
          __typename: value$5,
          id: value$4,
          firstName: value$3,
          lastName: value$2
        };
        var value$6 = value.from_;
        var value$7 = value$6.lastName;
        var value$8 = value$6.firstName;
        var value$9 = value$6.id;
        var value$10 = value$6.__typename;
        var from_ = {
          __typename: value$10,
          id: value$9,
          firstName: value$8,
          lastName: value$7
        };
        var value$11 = value.answered;
        var value$12 = value.timestamp;
        var value$13 = value.duration;
        var value$14 = value.id;
        var value$15 = value.__typename;
        return {
                __typename: value$15,
                id: value$14,
                duration: value$13,
                timestamp: value$12,
                answered: value$11,
                from_: from_,
                to_: to_
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
          calls: calls
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
