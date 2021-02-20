'use strict';

var Json = require("./Json.bs.js");
var Curry = require("bs-platform/lib/js/curry.js");
var $$Promise = require("reason-promise/src/js/promise.bs.js");

function get(db, path) {
  return $$Promise.Js.toResult(db.ref(path).once("value", undefined, undefined));
}

function onFinish(req, onOk) {
  return $$Promise.Js.map(req, (function (res) {
                if (res.TAG) {
                  return Json.fromObject(res._0);
                } else {
                  return Curry._1(onOk, res._0);
                }
              }));
}

exports.get = get;
exports.onFinish = onFinish;
/* Promise Not a pure module */
