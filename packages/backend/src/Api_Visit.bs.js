'use strict';

var Json = require("./Json.bs.js");
var Decco = require("decco/src/Decco.bs.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var $$Promise = require("reason-promise/src/js/promise.bs.js");
var JwtDecode = require("jwt-decode").default;
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

function createVisitPayload_encode(v) {
  return Js_dict.fromArray([
              [
                "patientId",
                Decco.stringToJson(v.patientId)
              ],
              [
                "from_",
                Decco.stringToJson(v.from_)
              ],
              [
                "to_",
                Decco.stringToJson(v.to_)
              ],
              [
                "notes",
                Decco.stringToJson(v.notes)
              ]
            ]);
}

function createVisitPayload_decode(v) {
  var dict = Js_json.classify(v);
  if (typeof dict === "number") {
    return Decco.error(undefined, "Not an object", v);
  }
  if (dict.TAG !== /* JSONObject */2) {
    return Decco.error(undefined, "Not an object", v);
  }
  var dict$1 = dict._0;
  var patientId = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "patientId"), null));
  if (patientId.TAG) {
    var e = patientId._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".patientId" + e.path,
              message: e.message,
              value: e.value
            }
          };
  }
  var from_ = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "from_"), null));
  if (from_.TAG) {
    var e$1 = from_._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".from_" + e$1.path,
              message: e$1.message,
              value: e$1.value
            }
          };
  }
  var to_ = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "to_"), null));
  if (to_.TAG) {
    var e$2 = to_._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".to_" + e$2.path,
              message: e$2.message,
              value: e$2.value
            }
          };
  }
  var notes = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "notes"), null));
  if (!notes.TAG) {
    return {
            TAG: /* Ok */0,
            _0: {
              patientId: patientId._0,
              from_: from_._0,
              to_: to_._0,
              notes: notes._0
            }
          };
  }
  var e$3 = notes._0;
  return {
          TAG: /* Error */1,
          _0: {
            path: ".notes" + e$3.path,
            message: e$3.message,
            value: e$3.value
          }
        };
}

function toRecord(payload, id) {
  return {
          from_: payload.from_,
          to_: payload.to_,
          id: id,
          notes: payload.notes,
          patientId: payload.patientId
        };
}

function createVisit(payload, context) {
  var match = JwtDecode(context.token);
  var createdRecordId = context.db.ref("/visits").push({
        patientId: payload.patientId,
        from_: payload.from_,
        to_: payload.to_,
        notes: payload.notes,
        doctorId: match.user_id
      }, undefined).key;
  if (createdRecordId == null) {
    return $$Promise.resolved(undefined);
  }
  var r = context.db.ref("/visits/" + createdRecordId);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                }
                var res$1 = createVisitPayload_decode(res._0.val());
                if (res$1.TAG) {
                  return Json.fromObject(res$1._0);
                } else {
                  return toRecord(res$1._0, createdRecordId);
                }
              }));
}

function remove(payload, context) {
  return $$Promise.Js.map($$Promise.Js.toResult(context.db.ref("/visits/" + payload.id).set(null, undefined)), (function (res) {
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
  var r = context.db.ref("/visits");
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                }
                var match = JwtDecode(context.token);
                return Json.toOwnedList(res._0, match.user_id, "doctor");
              }));
}

exports.createVisitPayload_encode = createVisitPayload_encode;
exports.createVisitPayload_decode = createVisitPayload_decode;
exports.toRecord = toRecord;
exports.createVisit = createVisit;
exports.remove = remove;
exports.list = list;
/* Promise Not a pure module */
