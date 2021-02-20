

import * as React from "react";
import * as Auth$Peaky from "./Auth.bs.js";
import * as Layout$Peaky from "./Layout.bs.js";
import * as Client from "@apollo/client";
import * as Calendar$Peaky from "./Calendar.bs.js";
import * as Settings$Peaky from "./Settings.bs.js";
import * as Call_View$Peaky from "./Call_View.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.bs.js";
import * as SignIn_View$Peaky from "./SignIn_View.bs.js";
import * as Consultations$Peaky from "./Consultations.bs.js";
import * as GraphqlClient$Peaky from "./GraphqlClient.bs.js";
import * as Calls_List_View$Peaky from "./Calls_List_View.bs.js";
import * as Consultation_Room$Peaky from "./Consultation_Room.bs.js";
import * as Patient_Chat_View$Peaky from "./Patient_Chat_View.bs.js";
import * as Patient_List_View$Peaky from "./Patient_List_View.bs.js";
import * as Patient_Details_View$Peaky from "./Patient_Details_View.bs.js";
import * as Patient_Video_Chat_View$Peaky from "./Patient_Video_Chat_View.bs.js";

function App(Props) {
  var token = Auth$Peaky.getToken(undefined);
  var url = ReasonReactRouter.useUrl(undefined, undefined);
  var tmp;
  if (token !== undefined) {
    var match = url.path;
    var tmp$1;
    if (match) {
      switch (match.hd) {
        case "calls" :
            var match$1 = match.tl;
            if (match$1) {
              var match$2 = match$1.tl;
              if (match$2) {
                var match$3 = match$2.tl;
                tmp$1 = match$3 && !match$3.tl ? React.createElement(Call_View$Peaky.make, {
                        id: match$1.hd,
                        patientId: match$3.hd,
                        doctorId: match$2.hd,
                        isPatient: false
                      }) : null;
              } else {
                tmp$1 = null;
              }
            } else {
              tmp$1 = React.createElement(Calls_List_View$Peaky.make, {});
            }
            break;
        case "consultations" :
            var match$4 = match.tl;
            tmp$1 = match$4 ? (
                match$4.tl ? null : React.createElement(Consultation_Room$Peaky.make, {
                        id: match$4.hd
                      })
              ) : React.createElement(Consultations$Peaky.make, {});
            break;
        case "patients" :
            var match$5 = match.tl;
            if (match$5) {
              var match$6 = match$5.tl;
              var id = match$5.hd;
              if (match$6) {
                switch (match$6.hd) {
                  case "chat" :
                      tmp$1 = match$6.tl ? null : React.createElement(Patient_Chat_View$Peaky.make, {
                              _id: id
                            });
                      break;
                  case "video" :
                      tmp$1 = match$6.tl ? null : React.createElement(Patient_Video_Chat_View$Peaky.make, {
                              id: id
                            });
                      break;
                  default:
                    tmp$1 = null;
                }
              } else {
                tmp$1 = React.createElement(Patient_Details_View$Peaky.make, {
                      id: id
                    });
              }
            } else {
              tmp$1 = React.createElement(Patient_List_View$Peaky.make, {});
            }
            break;
        case "settings" :
            tmp$1 = match.tl ? null : React.createElement(Settings$Peaky.make, {});
            break;
        default:
          tmp$1 = null;
      }
    } else {
      tmp$1 = React.createElement(Calendar$Peaky.make, {});
    }
    tmp = React.createElement(Layout$Peaky.make, {
          children: tmp$1
        });
  } else {
    var match$7 = url.path;
    var exit = 0;
    if (match$7 && match$7.hd === "calls") {
      var match$8 = match$7.tl;
      if (match$8) {
        var match$9 = match$8.tl;
        if (match$9) {
          var match$10 = match$9.tl;
          if (match$10 && !match$10.tl) {
            tmp = React.createElement(Call_View$Peaky.make, {
                  id: match$8.hd,
                  patientId: match$10.hd,
                  doctorId: match$9.hd,
                  isPatient: true
                });
          } else {
            exit = 1;
          }
        } else {
          exit = 1;
        }
      } else {
        exit = 1;
      }
    } else {
      exit = 1;
    }
    if (exit === 1) {
      tmp = React.createElement(SignIn_View$Peaky.make, {});
    }
    
  }
  return React.createElement(Client.ApolloProvider, {
              client: GraphqlClient$Peaky.instance,
              children: React.createElement("div", undefined, tmp)
            });
}

var make = App;

export {
  make ,
  
}
/* react Not a pure module */
