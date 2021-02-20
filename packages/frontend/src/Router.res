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
  | Settings

let toUrl = view =>
  switch view {
  | Calendar => "/"
  | Patients => "/patients"
  | PatientVideoChat(id) => j`/patients/$id/video`
  | PatientChat(id) => j`/patients/$id/chat`
  | Patient(id) => j`/patients/$id`
  | Consultations => "/consultations"
  | ConsultationRoom(id) => j`/consultations/$id`
  | Visit(id, doctorId, patientId) => j`/calls/$id/$doctorId/$patientId`
  | Visits => "/calls"
  | SignIn => "/sign-in"
  | Settings => "/settings"
  }

let toView = url =>
  switch url {
  | list{"patients", id, "chat"} => PatientChat(id)
  | list{"patients", id, "video"} => PatientVideoChat(id)
  | list{"patients", id} => Patient(id)
  | list{"consultations", id} => ConsultationRoom(id)
  | list{"consultations"} => Consultations
  | list{"calls", id, doctorId, patientId} => Visit(id, doctorId, patientId)
  | list{"calls"} => Visits
  | list{"patients"} => Patients
  | _ => Calendar
  }

let push = view => view->toUrl->ReasonReactRouter.push

@scope("history") @val external goBack: unit => unit = "back"
// [@bs.send] external back: (Dom.window, unit) => unit = "back";

// let goBack = () => [%bs.raw {|window.history.back()|}];
