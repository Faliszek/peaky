

import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";

function toUrl(view) {
  if (typeof view === "number") {
    switch (view) {
      case /* Calendar */0 :
          return "/";
      case /* Patients */1 :
          return "/patients";
      case /* Consultations */2 :
          return "/consultations";
      case /* Visits */3 :
          return "/calls";
      case /* SignIn */4 :
          return "/sign-in";
      case /* Settings */5 :
          return "/settings";
      
    }
  } else {
    switch (view.TAG | 0) {
      case /* PatientVideoChat */0 :
          return "/patients/" + view._0 + "/video";
      case /* PatientChat */1 :
          return "/patients/" + view._0 + "/chat";
      case /* Patient */2 :
          return "/patients/" + view._0;
      case /* ConsultationRoom */3 :
          return "/consultations/" + view._0;
      case /* Visit */4 :
          return "/calls/" + view._0 + "/" + view._1 + "/" + view._2;
      
    }
  }
}

function toView(url) {
  if (!url) {
    return /* Calendar */0;
  }
  switch (url.hd) {
    case "calls" :
        var match = url.tl;
        if (!match) {
          return /* Visits */3;
        }
        var match$1 = match.tl;
        if (!match$1) {
          return /* Calendar */0;
        }
        var match$2 = match$1.tl;
        if (match$2 && !match$2.tl) {
          return {
                  TAG: /* Visit */4,
                  _0: match.hd,
                  _1: match$1.hd,
                  _2: match$2.hd
                };
        } else {
          return /* Calendar */0;
        }
    case "consultations" :
        var match$3 = url.tl;
        if (match$3) {
          if (match$3.tl) {
            return /* Calendar */0;
          } else {
            return {
                    TAG: /* ConsultationRoom */3,
                    _0: match$3.hd
                  };
          }
        } else {
          return /* Consultations */2;
        }
    case "patients" :
        var match$4 = url.tl;
        if (!match$4) {
          return /* Patients */1;
        }
        var match$5 = match$4.tl;
        var id = match$4.hd;
        if (!match$5) {
          return {
                  TAG: /* Patient */2,
                  _0: id
                };
        }
        switch (match$5.hd) {
          case "chat" :
              if (match$5.tl) {
                return /* Calendar */0;
              } else {
                return {
                        TAG: /* PatientChat */1,
                        _0: id
                      };
              }
          case "video" :
              if (match$5.tl) {
                return /* Calendar */0;
              } else {
                return {
                        TAG: /* PatientVideoChat */0,
                        _0: id
                      };
              }
          default:
            return /* Calendar */0;
        }
    default:
      return /* Calendar */0;
  }
}

function push(view) {
  return ReasonReactRouter.push(toUrl(view));
}

export {
  toUrl ,
  toView ,
  push ,
  
}
/* ReasonReactRouter Not a pure module */
