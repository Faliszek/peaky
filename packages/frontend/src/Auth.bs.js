

import JwtDecode from "jwt-decode";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as Router$Peaky from "./Router.bs.js";
import * as ApolloClient__Link_Context from "reason-apollo-client/src/@apollo/client/link/context/ApolloClient__Link_Context.bs.js";

function getToken(param) {
  return Caml_option.null_to_opt(localStorage.getItem("token"));
}

function getUserId(param) {
  return JwtDecode(Caml_option.null_to_opt(localStorage.getItem("token"))).user_id;
}

function signIn(token) {
  if (token !== undefined) {
    localStorage.setItem("token", token);
    ApolloClient__Link_Context.setContext(function (param, param$1) {
          return {
                  Authorization: token
                };
        });
  }
  return Router$Peaky.push(/* Calendar */0);
}

function signOut(param) {
  localStorage.removeItem("token");
  return Router$Peaky.push(/* SignIn */4);
}

export {
  getToken ,
  getUserId ,
  signIn ,
  signOut ,
  
}
/* jwt-decode Not a pure module */
