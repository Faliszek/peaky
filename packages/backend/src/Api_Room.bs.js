'use strict';

var Json = require("./Json.bs.js");
var $$Promise = require("reason-promise/src/js/promise.bs.js");

function add(payload, context) {
  var createdRecordId = context.db.ref("/rooms").push(payload, undefined).key;
  if (createdRecordId == null) {
    return $$Promise.resolved(undefined);
  }
  var r = context.db.ref("/rooms/" + createdRecordId);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                } else {
                  return Json.toObject(res._0, createdRecordId);
                }
              }));
}

function get(payload, context) {
  var r = context.db.ref("/rooms/" + payload.id);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                } else {
                  return Json.toObject(res._0, payload.id);
                }
              }));
}

exports.add = add;
exports.get = get;
/* Promise Not a pure module */
