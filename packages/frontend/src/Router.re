type view =
  | Calendar
  | PatientVideoChat(string)
  | PatientChat(string)
  | Patient(string)
  | Patients
  | Consultations
  | ConsultationRoom(string)
  | Visit(string, string, string)
  | Visits
  | SignIn
  | Settings;

let toUrl = view =>
  switch (view) {
  | Calendar => "/"
  | Patients => "/patients"
  | PatientVideoChat(id) => {j|/patients/$id/video|j}
  | PatientChat(id) => {j|/patients/$id/chat|j}
  | Patient(id) => {j|/patients/$id|j}
  | Consultations => "/consultations"
  | ConsultationRoom(id) => {j|/consultations/$id|j}
  | Visit(id, doctorId, patientId) => {j|/calls/$id/$doctorId/$patientId|j}
  | Visits => "/calls"
  | SignIn => "/sign-in"
  | Settings => "/settings"
  };

let toView = url =>
  switch (url) {
  | ["patients", id, "chat"] => PatientChat(id)
  | ["patients", id, "video"] => PatientVideoChat(id)
  | ["patients", id] => Patient(id)
  | ["consultations", id] => ConsultationRoom(id)
  | ["consultations"] => Consultations
  | ["calls", id, doctorId, patientId] => Visit(id, doctorId, patientId)
  | ["calls"] => Visits
  | ["patients"] => Patients
  | _ => Calendar
  };

let push = view => view->toUrl->ReasonReactRouter.push;

[@bs.scope "history"] [@bs.val] external goBack: unit => unit = "back";
// [@bs.send] external back: (Dom.window, unit) => unit = "back";

// let goBack = () => [%bs.raw {|window.history.back()|}];
