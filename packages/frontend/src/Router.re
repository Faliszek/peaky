type view =
  | Calendar
  | Patients
  | Friends
  | Visits
  | SignIn;

let toUrl = view =>
  switch (view) {
  | Calendar => "/"
  | Patients => "/patients"
  | Friends => "/friends"
  | Visits => "/visits"
  | SignIn => "/sign-in"
  };

let toView = url =>
  switch (url) {
  | ["friends"] => Friends
  | ["visits"] => Visits
  | ["patients"] => Patients
  | _ => Calendar
  };

let push = view => view->toUrl->ReasonReactRouter.push;

// [@bs.send] external back: (Dom.window, unit) => unit = "back";

// let goBack = () => [%bs.raw {|window.history.back()|}];
