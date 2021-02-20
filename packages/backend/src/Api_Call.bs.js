'use strict';

var Json = require("./Json.bs.js");
var Chain = require("./Chain.bs.js");
var Decco = require("decco/src/Decco.bs.js");
var Domain = require("./Domain.bs.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var $$Promise = require("reason-promise/src/js/promise.bs.js");
var JwtDecode = require("jwt-decode").default;
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

function userData_encode(v) {
  return Js_dict.fromArray([
              [
                "email",
                Decco.stringToJson(v.email)
              ],
              [
                "specialization",
                Decco.stringToJson(v.specialization)
              ],
              [
                "firstName",
                Decco.stringToJson(v.firstName)
              ],
              [
                "lastName",
                Decco.stringToJson(v.lastName)
              ],
              [
                "patients",
                Decco.optionToJson((function (param) {
                        return Decco.arrayToJson(Domain.Patient.t_encode, param);
                      }), v.patients)
              ]
            ]);
}

function userData_decode(v) {
  var dict = Js_json.classify(v);
  if (typeof dict === "number") {
    return Decco.error(undefined, "Not an object", v);
  }
  if (dict.TAG !== /* JSONObject */2) {
    return Decco.error(undefined, "Not an object", v);
  }
  var dict$1 = dict._0;
  var email = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "email"), null));
  if (email.TAG) {
    var e = email._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".email" + e.path,
              message: e.message,
              value: e.value
            }
          };
  }
  var specialization = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "specialization"), null));
  if (specialization.TAG) {
    var e$1 = specialization._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".specialization" + e$1.path,
              message: e$1.message,
              value: e$1.value
            }
          };
  }
  var firstName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "firstName"), null));
  if (firstName.TAG) {
    var e$2 = firstName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".firstName" + e$2.path,
              message: e$2.message,
              value: e$2.value
            }
          };
  }
  var lastName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "lastName"), null));
  if (lastName.TAG) {
    var e$3 = lastName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".lastName" + e$3.path,
              message: e$3.message,
              value: e$3.value
            }
          };
  }
  var patients = Decco.optionFromJson((function (param) {
          return Decco.arrayFromJson(Domain.Patient.t_decode, param);
        }), Belt_Option.getWithDefault(Js_dict.get(dict$1, "patients"), null));
  if (!patients.TAG) {
    return {
            TAG: /* Ok */0,
            _0: {
              email: email._0,
              specialization: specialization._0,
              firstName: firstName._0,
              lastName: lastName._0,
              patients: patients._0
            }
          };
  }
  var e$4 = patients._0;
  return {
          TAG: /* Error */1,
          _0: {
            path: ".patients" + e$4.path,
            message: e$4.message,
            value: e$4.value
          }
        };
}

function userList_encode(v) {
  return Decco.arrayToJson(userData_encode, v);
}

function userList_decode(v) {
  return Decco.arrayFromJson(userData_decode, v);
}

function toRecord(id, payload) {
  return {
          email: payload.email,
          id: id,
          specialization: payload.specialization,
          firstName: payload.firstName,
          lastName: payload.lastName,
          patients: payload.patients
        };
}

function me(_payload, context) {
  var match = JwtDecode(context.token);
  var user_id = match.user_id;
  return $$Promise.Js.map($$Promise.Js.toResult(context.db.ref("/users/" + user_id).once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                }
                var res$1 = userData_decode(res._0.val());
                if (!res$1.TAG) {
                  return toRecord(user_id, res$1._0);
                }
                var err = res$1._0;
                console.log(err);
                return Json.fromObject(err);
              }));
}

function list(_payload, context) {
  return $$Promise.flatMap(Chain.onFinish(Chain.get(context.db, "/users"), Json.toList), (function (users) {
                return Chain.onFinish(Chain.get(context.db, "/calls"), (function (calls) {
                              return Json.toCallsList(calls, users);
                            }));
              }));
}

exports.userData_encode = userData_encode;
exports.userData_decode = userData_decode;
exports.userList_encode = userList_encode;
exports.userList_decode = userList_decode;
exports.toRecord = toRecord;
exports.me = me;
exports.list = list;
/* Chain Not a pure module */
