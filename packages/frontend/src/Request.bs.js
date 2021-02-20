

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as $$Promise from "reason-promise/src/js/promise.bs.js";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Error$Peaky from "./Error.bs.js";

function onFinish(req, onOk, onError) {
  return $$Promise.Js.get($$Promise.Js.toResult($$Promise.Js.fromBsPromise(req)), (function (res) {
                console.log(res);
                if (res.TAG !== /* Ok */0) {
                  return Error$Peaky.handleError("Coś poszło nie tak", res._0);
                }
                var res$1 = res._0;
                if (res$1.TAG === /* Ok */0) {
                  var res$2 = res$1._0;
                  console.log("REST", res$2);
                  Curry._1(onOk, res$2.data);
                  Belt_Option.map(res$2.error, (function (err) {
                          return Error$Peaky.handleError("Domain error (?)", err);
                        }));
                  return ;
                }
                var error = res$1._0;
                var match = error.networkError;
                var match$1 = error.graphQLErrors;
                if (match !== undefined) {
                  return Error$Peaky.handleError("Network error", "Nie mogliśmy nawiązać połączenia z serwerem, sprawdzamy co się dzieje");
                } else {
                  Error$Peaky.handleError("Probably domain error", match$1);
                  return Curry._1(onError, match$1);
                }
              }));
}

export {
  onFinish ,
  
}
/* Promise Not a pure module */
