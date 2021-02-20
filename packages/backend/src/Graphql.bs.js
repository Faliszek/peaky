'use strict';

var Api_Call = require("./Api_Call.bs.js");
var Api_Room = require("./Api_Room.bs.js");
var Api_User = require("./Api_User.bs.js");
var Api_Visit = require("./Api_Visit.bs.js");
var Api_Feeling = require("./Api_Feeling.bs.js");
var Api_Patient = require("./Api_Patient.bs.js");
var Api_Symptom = require("./Api_Symptom.bs.js");
var Graphql_Auth = require("./Graphql_Auth.bs.js");
var Api_PatientEvent = require("./Api_PatientEvent.bs.js");
var Api_Consultations = require("./Api_Consultations.bs.js");

var root = {
  signIn: Graphql_Auth.signIn,
  signUp: Graphql_Auth.signUp,
  createVisit: Api_Visit.createVisit,
  removeVisit: Api_Visit.remove,
  createPatient: Api_Patient.createPatient,
  removePatient: Api_Patient.removePatient,
  me: Api_User.me,
  searchSpecialist: Api_User.search,
  patients: Api_Patient.list,
  patient: Api_Patient.single,
  visits: Api_Visit.list,
  calls: Api_Call.list,
  addFeeling: Api_Feeling.add,
  addPatientEvent: Api_PatientEvent.add,
  addSymptom: Api_Symptom.add,
  feelings: Api_Feeling.list,
  patientEvents: Api_PatientEvent.list,
  symptoms: Api_Symptom.list,
  createRoom: Api_Room.add,
  getRoom: Api_Room.get,
  consultations: Api_Consultations.list,
  createConsultation: Api_Consultations.create,
  decline: Api_Consultations.decline,
  users: Api_User.list,
  consultation: Api_Consultations.single
};

exports.root = root;
/* Api_Call Not a pure module */
