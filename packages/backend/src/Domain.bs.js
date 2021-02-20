'use strict';

var Decco = require("decco/src/Decco.bs.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

function sympmtom_encode(v) {
  return Js_dict.fromArray([
              [
                "id",
                Decco.stringToJson(v.id)
              ],
              [
                "name",
                Decco.stringToJson(v.name)
              ]
            ]);
}

function sympmtom_decode(v) {
  var dict = Js_json.classify(v);
  if (typeof dict === "number") {
    return Decco.error(undefined, "Not an object", v);
  }
  if (dict.TAG !== /* JSONObject */2) {
    return Decco.error(undefined, "Not an object", v);
  }
  var dict$1 = dict._0;
  var id = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "id"), null));
  if (id.TAG) {
    var e = id._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".id" + e.path,
              message: e.message,
              value: e.value
            }
          };
  }
  var name = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "name"), null));
  if (!name.TAG) {
    return {
            TAG: /* Ok */0,
            _0: {
              id: id._0,
              name: name._0
            }
          };
  }
  var e$1 = name._0;
  return {
          TAG: /* Error */1,
          _0: {
            path: ".name" + e$1.path,
            message: e$1.message,
            value: e$1.value
          }
        };
}

function event_encode(v) {
  return Js_dict.fromArray([
              [
                "symptomps",
                Decco.listToJson(sympmtom_encode, v.symptomps)
              ],
              [
                "feeling",
                Decco.intToJson(v.feeling)
              ],
              [
                "timestamp",
                Decco.floatToJson(v.timestamp)
              ]
            ]);
}

function event_decode(v) {
  var dict = Js_json.classify(v);
  if (typeof dict === "number") {
    return Decco.error(undefined, "Not an object", v);
  }
  if (dict.TAG !== /* JSONObject */2) {
    return Decco.error(undefined, "Not an object", v);
  }
  var dict$1 = dict._0;
  var symptomps = Decco.listFromJson(sympmtom_decode, Belt_Option.getWithDefault(Js_dict.get(dict$1, "symptomps"), null));
  if (symptomps.TAG) {
    var e = symptomps._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".symptomps" + e.path,
              message: e.message,
              value: e.value
            }
          };
  }
  var feeling = Decco.intFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "feeling"), null));
  if (feeling.TAG) {
    var e$1 = feeling._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".feeling" + e$1.path,
              message: e$1.message,
              value: e$1.value
            }
          };
  }
  var timestamp = Decco.floatFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "timestamp"), null));
  if (!timestamp.TAG) {
    return {
            TAG: /* Ok */0,
            _0: {
              symptomps: symptomps._0,
              feeling: feeling._0,
              timestamp: timestamp._0
            }
          };
  }
  var e$2 = timestamp._0;
  return {
          TAG: /* Error */1,
          _0: {
            path: ".timestamp" + e$2.path,
            message: e$2.message,
            value: e$2.value
          }
        };
}

function t_encode(v) {
  return Js_dict.fromArray([
              [
                "id",
                Decco.stringToJson(v.id)
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
                "phoneNumber",
                Decco.stringToJson(v.phoneNumber)
              ],
              [
                "disease",
                Decco.stringToJson(v.disease)
              ],
              [
                "treatment",
                Decco.listToJson(event_encode, v.treatment)
              ],
              [
                "color",
                Decco.stringToJson(v.color)
              ]
            ]);
}

function t_decode(v) {
  var dict = Js_json.classify(v);
  if (typeof dict === "number") {
    return Decco.error(undefined, "Not an object", v);
  }
  if (dict.TAG !== /* JSONObject */2) {
    return Decco.error(undefined, "Not an object", v);
  }
  var dict$1 = dict._0;
  var id = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "id"), null));
  if (id.TAG) {
    var e = id._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".id" + e.path,
              message: e.message,
              value: e.value
            }
          };
  }
  var firstName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "firstName"), null));
  if (firstName.TAG) {
    var e$1 = firstName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".firstName" + e$1.path,
              message: e$1.message,
              value: e$1.value
            }
          };
  }
  var lastName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "lastName"), null));
  if (lastName.TAG) {
    var e$2 = lastName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".lastName" + e$2.path,
              message: e$2.message,
              value: e$2.value
            }
          };
  }
  var phoneNumber = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "phoneNumber"), null));
  if (phoneNumber.TAG) {
    var e$3 = phoneNumber._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".phoneNumber" + e$3.path,
              message: e$3.message,
              value: e$3.value
            }
          };
  }
  var disease = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "disease"), null));
  if (disease.TAG) {
    var e$4 = disease._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".disease" + e$4.path,
              message: e$4.message,
              value: e$4.value
            }
          };
  }
  var treatment = Decco.listFromJson(event_decode, Belt_Option.getWithDefault(Js_dict.get(dict$1, "treatment"), null));
  if (treatment.TAG) {
    var e$5 = treatment._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".treatment" + e$5.path,
              message: e$5.message,
              value: e$5.value
            }
          };
  }
  var color = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "color"), null));
  if (!color.TAG) {
    return {
            TAG: /* Ok */0,
            _0: {
              id: id._0,
              firstName: firstName._0,
              lastName: lastName._0,
              phoneNumber: phoneNumber._0,
              disease: disease._0,
              treatment: treatment._0,
              color: color._0
            }
          };
  }
  var e$6 = color._0;
  return {
          TAG: /* Error */1,
          _0: {
            path: ".color" + e$6.path,
            message: e$6.message,
            value: e$6.value
          }
        };
}

function list_encode(v) {
  return Decco.arrayToJson(t_encode, v);
}

function list_decode(v) {
  return Decco.arrayFromJson(t_decode, v);
}

var Patient = {
  sympmtom_encode: sympmtom_encode,
  sympmtom_decode: sympmtom_decode,
  event_encode: event_encode,
  event_decode: event_decode,
  t_encode: t_encode,
  t_decode: t_decode,
  list_encode: list_encode,
  list_decode: list_decode
};

function t_encode$1(v) {
  return Js_dict.fromArray([
              [
                "email",
                Decco.stringToJson(v.email)
              ],
              [
                "id",
                Decco.stringToJson(v.id)
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
                        return Decco.arrayToJson(t_encode, param);
                      }), v.patients)
              ]
            ]);
}

function t_decode$1(v) {
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
  var id = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "id"), null));
  if (id.TAG) {
    var e$1 = id._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".id" + e$1.path,
              message: e$1.message,
              value: e$1.value
            }
          };
  }
  var specialization = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "specialization"), null));
  if (specialization.TAG) {
    var e$2 = specialization._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".specialization" + e$2.path,
              message: e$2.message,
              value: e$2.value
            }
          };
  }
  var firstName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "firstName"), null));
  if (firstName.TAG) {
    var e$3 = firstName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".firstName" + e$3.path,
              message: e$3.message,
              value: e$3.value
            }
          };
  }
  var lastName = Decco.stringFromJson(Belt_Option.getWithDefault(Js_dict.get(dict$1, "lastName"), null));
  if (lastName.TAG) {
    var e$4 = lastName._0;
    return {
            TAG: /* Error */1,
            _0: {
              path: ".lastName" + e$4.path,
              message: e$4.message,
              value: e$4.value
            }
          };
  }
  var patients = Decco.optionFromJson((function (param) {
          return Decco.arrayFromJson(t_decode, param);
        }), Belt_Option.getWithDefault(Js_dict.get(dict$1, "patients"), null));
  if (!patients.TAG) {
    return {
            TAG: /* Ok */0,
            _0: {
              email: email._0,
              id: id._0,
              specialization: specialization._0,
              firstName: firstName._0,
              lastName: lastName._0,
              patients: patients._0
            }
          };
  }
  var e$5 = patients._0;
  return {
          TAG: /* Error */1,
          _0: {
            path: ".patients" + e$5.path,
            message: e$5.message,
            value: e$5.value
          }
        };
}

var User = {
  t_encode: t_encode$1,
  t_decode: t_decode$1
};

var Call = {};

var Visit = {};

var Feeling = {};

var PatientEvent = {};

var Symptom = {};

var Room = {};

var Consultation = {};

exports.Patient = Patient;
exports.User = User;
exports.Call = Call;
exports.Visit = Visit;
exports.Feeling = Feeling;
exports.PatientEvent = PatientEvent;
exports.Symptom = Symptom;
exports.Room = Room;
exports.Consultation = Consultation;
/* No side effect */
