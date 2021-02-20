'use strict';

var Json = require("./Json.bs.js");
var Chain = require("./Chain.bs.js");
var $$Promise = require("reason-promise/src/js/promise.bs.js");

function add(payload, context) {
  var createdRecordId = context.db.ref("/symptoms").push(payload, undefined).key;
  if (createdRecordId == null) {
    return $$Promise.resolved(undefined);
  }
  var r = context.db.ref("/symptoms/" + createdRecordId);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                } else {
                  return Json.toObject(res._0, createdRecordId);
                }
              }));
}

function list(payload, context) {
  return Chain.onFinish(Chain.get(context.db, "/symptoms"), (function (feelings) {
                return Json.toOwnedList(feelings, payload.patientId, "patient");
              }));
}

exports.add = add;
exports.list = list;
/* Chain Not a pure module */
