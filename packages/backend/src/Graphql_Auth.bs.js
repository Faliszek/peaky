'use strict';

var $$Promise = require("reason-promise/src/js/promise.bs.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

function signIn(param, context) {
  return $$Promise.Js.map($$Promise.Js.flatMap(context.auth.signInWithEmailAndPassword(param.email, param.password), (function (res) {
                    return res.user.getIdToken();
                  })), (function (prim) {
                if (prim == null) {
                  return ;
                } else {
                  return Caml_option.some(prim);
                }
              }));
}

function createUser(db, uid, email) {
  var partial_arg = {
    email: email
  };
  var partial_arg$1 = db.ref("/users/" + uid);
  return function (param, param$1) {
    return partial_arg$1.set(partial_arg, param !== undefined ? Caml_option.valFromOption(param) : undefined);
  };
}

function signUp(param, context) {
  return $$Promise.Js.relax($$Promise.Js.map($$Promise.Js.toResult(context.auth.createUserWithEmailAndPassword(param.email, param.password)), (function (res) {
                    if (res.TAG) {
                      return ;
                    }
                    var res$1 = res._0;
                    createUser(context.db, res$1.user.uid, res$1.user.email)(undefined, undefined);
                    return res$1.user;
                  })));
}

exports.signIn = signIn;
exports.createUser = createUser;
exports.signUp = signUp;
/* Promise Not a pure module */
