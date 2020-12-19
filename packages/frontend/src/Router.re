type view =
  | Calendar
  | PatientVideoChat(string)
  | PatientChat(string)
  | Patient(string)
  | Patients
  | Friends
  | Visits
  | SignIn;

let toUrl = view =>
  switch (view) {
  | Calendar => "/"
  | Patients => "/patients"
  | PatientVideoChat(id) => {j|/patients/$id/video|j}
  | PatientChat(id) => {j|/patients/$id/chat|j}
  | Patient(id) => {j|/patients/$id|j}
  | Friends => "/friends"
  | Visits => "/visits"
  | SignIn => "/sign-in"
  };

let toView = url =>
  switch (url) {
  | ["patients", id, "chat"] => PatientChat(id)
  | ["patients", id, "video"] => PatientVideoChat(id)
  | ["patients", id] => Patient(id)
  | ["friends"] => Friends
  | ["visits"] => Visits
  | ["patients"] => Patients
  | _ => Calendar
  };

let push = view => view->toUrl->ReasonReactRouter.push;

[@bs.scope "history"] [@bs.val] external goBack: unit => unit = "back";
// [@bs.send] external back: (Dom.window, unit) => unit = "back";

// let goBack = () => [%bs.raw {|window.history.back()|}];
