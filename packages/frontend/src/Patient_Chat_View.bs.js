

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Input$Peaky from "./components/Input.bs.js";
import * as Avatar$Peaky from "./components/Avatar.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as ReactFeather from "react-feather";

var messages = [];

function Patient_Chat_View$Status(Props) {
  var status = Props.status;
  var className = Props.className;
  var bg = status === "online" ? "bg-green-300" : "bg-red-300";
  return React.createElement("div", {
              className: Cn.$plus(Cn.$plus("w-4 h-4 rounded-full", bg), Cn.mapSome(className, (function (x) {
                          return x;
                        })))
            });
}

var Status = {
  make: Patient_Chat_View$Status
};

function Patient_Chat_View$Message(Props) {
  var text = Props.text;
  return React.createElement("div", undefined, React.createElement(Text$Peaky.make, {
                  children: text
                }));
}

var Message = {
  make: Patient_Chat_View$Message
};

function Patient_Chat_View(Props) {
  var lastName = "Smith";
  var firstName = "Adam";
  var name = firstName + (" " + lastName);
  var textarea = React.useRef(null);
  var match = React.useState(function () {
        return "";
      });
  var setMessage = match[1];
  React.useEffect((function () {
          var textarea$1 = textarea.current;
          if (!(textarea$1 == null)) {
            textarea$1.focus();
          }
          
        }), [textarea]);
  return React.createElement("div", {
              className: "flex flex-col h-screen w-full relative"
            }, React.createElement("div", {
                  className: "w-full shadow-lg px-4 flex flex-row items-center absolute top-0 h-28 justify-between"
                }, React.createElement("div", {
                      className: "flex justify-center items-center"
                    }, React.createElement(Avatar$Peaky.make, {
                          firstName: firstName,
                          lastName: lastName
                        }), React.createElement("h1", {
                          className: "ml-8 text-3xl"
                        }, React.createElement(Text$Peaky.make, {
                              children: name
                            })), React.createElement(Patient_Chat_View$Status, {
                          status: "online",
                          className: "ml-4"
                        })), React.createElement("div", undefined, React.createElement(Button$Peaky.CTA.make, {
                          children: React.createElement(Text$Peaky.make, {
                                children: "Dodaj wizytę"
                              }),
                          icon: React.createElement(ReactFeather.Plus, {
                                className: "mr-4"
                              })
                        }))), React.createElement("div", {
                  className: "w-full h-full flex flex-col pt-28 pb-36"
                }, React.createElement("div", {
                      className: "bg-gray-50 flex-1  overflow-y-auto"
                    }, messages.length !== 0 ? Belt_Array.map(messages, (function (m) {
                              return React.createElement(Patient_Chat_View$Message, {
                                          text: m.text
                                        });
                            })) : React.createElement("div", {
                            className: "text-gray-300 h-full flex items-center flex-col justify-center"
                          }, React.createElement(ReactFeather.Inbox, {
                                size: "64"
                              }), React.createElement("span", {
                                className: "mt-4 text-4xl"
                              }, React.createElement(Text$Peaky.make, {
                                    children: "Brak wiadomości"
                                  })))), React.createElement("div", {
                      className: "p-4 absolute bottom-0 h-36 border-top border flex items-center justify-center w-full"
                    }, React.createElement(Input$Peaky.Textarea.make, {
                          placeholder: "Napisz wiadomość",
                          ref_: textarea,
                          value: match[0],
                          onChange: (function (v) {
                              return Curry._1(setMessage, (function (param) {
                                            return v;
                                          }));
                            })
                        }), React.createElement(Button$Peaky.SmallRound.make, {
                          icon: React.createElement(ReactFeather.Send, {}),
                          onClick: (function (param) {
                              
                            })
                        }))));
}

var patient = {
  id: 1,
  firstName: "Adam",
  lastName: "Smith",
  disease: "Depresja",
  condition: "Dobry",
  avatar: "https://www.thispersondoesnotexist.com/image",
  phoneNumber: "+48 674 300 232",
  lastVisit: undefined
};

var make = Patient_Chat_View;

export {
  patient ,
  messages ,
  Status ,
  Message ,
  make ,
  
}
/* react Not a pure module */
