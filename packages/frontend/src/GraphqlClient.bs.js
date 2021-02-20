

import * as Auth$Peaky from "./Auth.bs.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as ApolloClient from "reason-apollo-client/src/ApolloClient.bs.js";
import * as ApolloClient__Link_Ws from "reason-apollo-client/src/@apollo/client/link/ws/ApolloClient__Link_Ws.bs.js";
import * as ApolloClient__Utilities from "reason-apollo-client/src/@apollo/client/utilities/ApolloClient__Utilities.bs.js";
import * as ApolloClient__ApolloClient from "reason-apollo-client/src/@apollo/client/ApolloClient__ApolloClient.bs.js";
import * as ApolloClient__Link_Context from "reason-apollo-client/src/@apollo/client/link/context/ApolloClient__Link_Context.bs.js";
import * as ReasonMLCommunity__ApolloClient from "reason-apollo-client/src/ReasonMLCommunity__ApolloClient.bs.js";
import * as ApolloClient__Link_Http_HttpLink from "reason-apollo-client/src/@apollo/client/link/http/ApolloClient__Link_Http_HttpLink.bs.js";
import * as ApolloClient__SubscriptionsTransportWs from "reason-apollo-client/src/subscriptions-transport-ws/ApolloClient__SubscriptionsTransportWs.bs.js";
import * as ApolloClient__Cache_InMemory_InMemoryCache from "reason-apollo-client/src/@apollo/client/cache/inmemory/ApolloClient__Cache_InMemory_InMemoryCache.bs.js";

var graphqlEndpoint = "localhost:4000/graphql";

var subscriptionEndpoint = "localhost:4001/subscriptions";

var headers = {
  high: "five"
};

var httpLink = ApolloClient__Link_Http_HttpLink.make((function (param) {
        return "http://localhost:4000/graphql";
      }), undefined, undefined, Caml_option.some(headers), undefined, undefined, undefined, undefined);

var wsLink = ApolloClient__Link_Ws.WebSocketLink.make("ws://localhost:4001/subscriptions", ApolloClient__SubscriptionsTransportWs.ClientOptions.make({
          TAG: /* ConnectionParams */0,
          _0: {
            headers: headers
          }
        }, undefined, true, undefined, undefined, undefined, undefined, undefined), undefined, undefined);

function authPayload(token) {
  return {
          headers: {
            Authorization: token
          }
        };
}

var authLink = ApolloClient__Link_Context.setContext(function (param, param$1) {
      var token = Auth$Peaky.getToken(undefined);
      if (token !== undefined) {
        return authPayload(token);
      } else {
        return {};
      }
    });

var terminatingLink = ReasonMLCommunity__ApolloClient.Link.split((function (param) {
        var definition = ApolloClient__Utilities.getOperationDefinition(param.query);
        if (definition !== undefined && definition.kind === "OperationDefinition") {
          return definition.operation === "subscription";
        } else {
          return false;
        }
      }), wsLink, httpLink);

var instance = ApolloClient.make(undefined, undefined, undefined, Caml_option.some(ReasonMLCommunity__ApolloClient.Link.concat(authLink, httpLink)), ApolloClient__Cache_InMemory_InMemoryCache.make(undefined, undefined, undefined, undefined, undefined, undefined), undefined, undefined, true, undefined, ApolloClient__ApolloClient.DefaultOptions.make(ApolloClient__ApolloClient.DefaultMutateOptions.make(undefined, undefined, true, /* All */2, undefined, undefined), ApolloClient__ApolloClient.DefaultQueryOptions.make(/* NetworkOnly */2, /* All */2, undefined, undefined), ApolloClient__ApolloClient.DefaultWatchQueryOptions.make(/* NetworkOnly */3, /* All */2, undefined, undefined), undefined), undefined, undefined, undefined, undefined, undefined, undefined, undefined);

export {
  graphqlEndpoint ,
  subscriptionEndpoint ,
  headers ,
  httpLink ,
  wsLink ,
  authPayload ,
  authLink ,
  terminatingLink ,
  instance ,
  
}
/* httpLink Not a pure module */
