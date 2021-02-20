'use strict';

var Json = require("./Json.bs.js");
var Chain = require("./Chain.bs.js");
var $$Promise = require("reason-promise/src/js/promise.bs.js");

function list(_payload, context) {
  return Chain.onFinish(Chain.get(context.db, "/consultations"), Json.toList);
}

function create(payload, context) {
  var createdRecordId = context.db.ref("/consultations").push(payload, undefined).key;
  if (createdRecordId == null) {
    return $$Promise.resolved(undefined);
  }
  var r = context.db.ref("/consultations/" + createdRecordId);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                } else {
                  return Json.toObject(res._0, createdRecordId);
                }
              }));
}

function decline(payload, context) {
  return $$Promise.Js.map($$Promise.Js.toResult(context.db.ref("/consultations/" + payload.id).set({
                      callerId: payload.callerId,
                      userIds: payload.userIds
                    }, undefined)), (function (res) {
                if (res.TAG) {
                  return ;
                } else {
                  return {
                          id: payload.id,
                          userIds: payload.userIds,
                          callerId: payload.callerId
                        };
                }
              }));
}

function single(payload, context) {
  var r = context.db.ref("/consultations/" + payload.id);
  return $$Promise.Js.map($$Promise.Js.toResult(r.once("value", undefined, undefined)), (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                } else {
                  return Json.toObject(res._0, payload.id);
                }
              }));
}

exports.list = list;
exports.create = create;
exports.decline = decline;
exports.single = single;
/* Chain Not a pure module */
