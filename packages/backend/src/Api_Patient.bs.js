'use strict';

var Json = require("./Json.bs.js");
var Decco = require("decco/src/Decco.bs.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var $$Promise = require("reason-promise/src/js/promise.bs.js");
var JwtDecode = require("jwt-decode").default;
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

function createPatientPayload_encode(v) {
  return Js_dict.fromArray([
              [
                "firstName",
                Decco.stringToJson(v.firstName)
              ],
              [
                "lastName",
                Decco.stringToJson(v.lastName)
              ],
              [
                "phoneNumber",
                Decco.stringToJson(v.phoneNumber)
              ],
              [
                "disease",
                Decco.stringToJson(v.disease)
              ],
              [
                "color",
                Decco.stringToJson(v.color)
              ]
            ]);
}

function createPatientPayload_decode(v) {
  var dict = Js_json.classify(v);
  if (typeof dict === "number") {
    return Decco.error(undefined, "Not an object", v);
  }
  if (dict.TAG !== /* JSONObject */2) {
    return Decco.error(undefined, "Not an object", v);
  }
  var dict$1 = dict._0;
  var firstName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "firstName"), null));
  if (firstName.TAG) {
    var e = firstName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".firstName" + e.path,
              message: e.message,
              value: e.value
            }
          };
  }
  var lastName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "lastName"), null));
  if (lastName.TAG) {
    var e$1 = lastName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".lastName" + e$1.path,
              message: e$1.message,
              value: e$1.value
            }
          };
  }
  var phoneNumber = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "phoneNumber"), null));
  if (phoneNumber.TAG) {
    var e$2 = phoneNumber._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".phoneNumber" + e$2.path,
              message: e$2.message,
              value: e$2.value
            }
          };
  }
  var disease = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "disease"), null));
  if (disease.TAG) {
    var e$3 = disease._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".disease" + e$3.path,
              message: e$3.message,
              value: e$3.value
            }
          };
  }
  var color = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "color"), null));
  if (!color.TAG) {
    return {
            TAG: /* Ok */0,
            _0: {
              firstName: firstName._0,
              lastName: lastName._0,
              phoneNumber: phoneNumber._0,
              disease: disease._0,
              color: color._0
            }
          };
  }
  var e$4 = color._0;
  return {
          TAG: /* Error */1,
          _0: {
            path: ".color" + e$4.path,
            message: e$4.message,
            value: e$4.value
          }
        };
}

function toRecord(payload, id) {
  return {
          id: id,
          firstName: payload.firstName,
          lastName: payload.lastName,
          phoneNumber: payload.phoneNumber,
          disease: payload.disease,
          treatment: /* [] */0,
          color: payload.color
        };
}

function createPatient(payload, context) {
  var match = JwtDecode(context.token);
  var createdRecordId = context.db.ref("/patients").push({
        firstName: payload.firstName,
        lastName: payload.lastName,
        phoneNumber: payload.phoneNumber,
        disease: payload.disease,
        doctorId: match.user_id,
        color: payload.color
      }, undefined).key;
  if (createdRecordId == null) {
    return $$Promise.resolved(undefined);
  }
  var r = context.db.ref("/patients/" + createdRecordId);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                }
                var res$1 = createPatientPayload_decode(res._0.val());
                if (res$1.TAG) {
                  return Json.fromObject(res$1._0);
                } else {
                  return toRecord(res$1._0, createdRecordId);
                }
              }));
}

function removePatient(payload, context) {
  return $$Promise.Js.map($$Promise.Js.toResult(context.db.ref("/patients/" + payload.id).set(null, undefined)), (function (res) {
                if (res.TAG) {
                  return ;
                } else {
                  return {
                          id: payload.id
                        };
                }
              }));
}

function list(_payload, context) {
  var r = context.db.ref("/patients");
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                console.log(res);
                if (res.TAG) {
                  return Json.fromObject(res._0);
                }
                var match = JwtDecode(context.token);
                return Json.toOwnedList(res._0, match.user_id, "doctor");
              }));
}

function single(payload, context) {
  var r = context.db.ref("/patients/" + payload.id);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                } else {
                  return Json.toObject(res._0, payload.id);
                }
              }));
}

exports.createPatientPayload_encode = createPatientPayload_encode;
exports.createPatientPayload_decode = createPatientPayload_decode;
exports.toRecord = toRecord;
exports.createPatient = createPatient;
exports.removePatient = removePatient;
exports.list = list;
exports.single = single;
/* Promise Not a pure module */
