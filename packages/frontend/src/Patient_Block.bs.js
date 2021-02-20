

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as React from "react";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Avatar$Peaky from "./components/Avatar.bs.js";
import * as Router$Peaky from "./Router.bs.js";
import * as ReactFeather from "react-feather";

function Patient_Block$Info(Props) {
  var name = Props.name;
  var phoneNumber = Props.phoneNumber;
  var disease = Props.disease;
  var lastVisit = Props.lastVisit;
  return React.createElement("div", {
              className: "py-2 px-4 ml-12"
            }, React.createElement("div", {
                  className: "text-xl font-medium text-gray-700"
                }, React.createElement(Text$Peaky.make, {
                      children: name
                    })), React.createElement("div", {
                  className: "text-lg mb-2 text-gray-600 "
                }, React.createElement(Text$Peaky.make, {
                      children: phoneNumber
                    })), React.createElement("div", {
                  className: "text-lg "
                }, React.createElement("span", {
                      className: "text-gray-400"
                    }, React.createElement(Text$Peaky.make, {
                          children: "Przypadłość: "
                        })), React.createElement("span", {
                      className: "text-gray-500"
                    }, React.createElement(Text$Peaky.make, {
                          children: disease
                        }))), React.createElement("div", {
                  className: "text-lg "
                }, React.createElement("span", {
                      className: "text-gray-400"
                    }, React.createElement(Text$Peaky.make, {
                          children: "Ostatnia wizyta: "
                        })), React.createElement("span", {
                      className: "text-gray-500"
                    }, React.createElement(Text$Peaky.make, {
                          children: Belt_Option.getWithDefault(lastVisit, "-")
                        }))));
}

var Info = {
  make: Patient_Block$Info
};

function Patient_Block$Link(Props) {
  return React.createElement("div", {
              className: "text-green-500 flex items-center"
            }, React.createElement(Text$Peaky.make, {
                  children: "Zobacz więcej"
                }), React.createElement(ReactFeather.ArrowRight, {
                  size: "16",
                  className: "ml-1"
                }));
}

var Link = {
  make: Patient_Block$Link
};

function Patient_Block(Props) {
  var patient = Props.patient;
  var className = Props.className;
  var lastName = patient.lastName;
  var firstName = patient.firstName;
  var id = patient.id;
  var name = firstName + (" " + lastName);
  return React.createElement("div", {
              className: Cn.mapSome(className, (function (x) {
                      return x;
                    })),
              onClick: (function (param) {
                  return Router$Peaky.push({
                              TAG: /* Patient */2,
                              _0: id
                            });
                })
            }, React.createElement("div", {
                  className: "m-4 px-4 py-6 flex flex-col w-full h-full shadow-lg rounded-lg cursor-pointer transition-all transform-gpu hover:shadow-lg hover:bg-gray-50"
                }, React.createElement("div", {
                      className: "flex flex-1"
                    }, React.createElement(Avatar$Peaky.make, {
                          firstName: firstName,
                          lastName: lastName,
                          color: patient.color
                        }), React.createElement(Patient_Block$Info, {
                          name: name,
                          phoneNumber: patient.phoneNumber,
                          disease: patient.disease,
                          lastVisit: patient.lastVisit
                        })), React.createElement("div", {
                      className: "flex justify-end"
                    }, React.createElement(Patient_Block$Link, {}))));
}

var make = Patient_Block;

export {
  Info ,
  Link ,
  make ,
  
}
/* react Not a pure module */
