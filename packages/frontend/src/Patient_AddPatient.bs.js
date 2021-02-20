

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Input$Peaky from "./components/Input.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as SideNav$Peaky from "./components/SideNav.bs.js";
import * as ReactFeather from "react-feather";
import * as Color_Picker$Peaky from "./Color_Picker.bs.js";

function Patient_AddPatient(Props) {
  var visible = Props.visible;
  var onClose = Props.onClose;
  var onCreate = Props.onCreate;
  var loading = Props.loading;
  var match = React.useState(function () {
        return "";
      });
  var setFirstName = match[1];
  var firstName = match[0];
  var match$1 = React.useState(function () {
        return "";
      });
  var setLastName = match$1[1];
  var lastName = match$1[0];
  var match$2 = React.useState(function () {
        return "";
      });
  var setPhoneNumber = match$2[1];
  var phoneNumber = match$2[0];
  var match$3 = React.useState(function () {
        return "";
      });
  var setDisease = match$3[1];
  var disease = match$3[0];
  var match$4 = React.useState(function () {
        return "";
      });
  var setColor = match$4[1];
  var color = match$4[0];
  return React.createElement(SideNav$Peaky.make, {
              visible: visible,
              onClose: onClose,
              title: "Dodawanie pacjenta",
              children: null
            }, React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: firstName,
                        onChange: (function (v) {
                            return Curry._1(setFirstName, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Imię"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: lastName,
                        onChange: (function (v) {
                            return Curry._1(setLastName, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Nazwisko"
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: phoneNumber,
                        onChange: (function (v) {
                            return Curry._1(setPhoneNumber, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Numer telefonu",
                        icon: React.createElement(ReactFeather.Phone, {})
                      })
                }), React.createElement(Input$Peaky.Wrap.make, {
                  children: React.createElement(Input$Peaky.make, {
                        value: disease,
                        onChange: (function (v) {
                            return Curry._1(setDisease, (function (param) {
                                          return v;
                                        }));
                          }),
                        placeholder: "Przypadłość",
                        icon: React.createElement(ReactFeather.Thermometer, {})
                      })
                }), React.createElement(Color_Picker$Peaky.make, {
                  value: color,
                  onChange: (function (v) {
                      return Curry._1(setColor, (function (param) {
                                    return v;
                                  }));
                    })
                }), React.createElement("div", {
                  className: "flex justify-center"
                }, React.createElement(Button$Peaky.CTA.make, {
                      loading: loading,
                      children: React.createElement(Text$Peaky.make, {
                            children: "Dodaj pacjenta"
                          }),
                      icon: React.createElement(ReactFeather.Plus, {
                            className: "mr-4"
                          }),
                      onClick: (function (param) {
                          Curry._5(onCreate, firstName, lastName, phoneNumber, disease, color);
                          
                        })
                    })));
}

var make = Patient_AddPatient;

export {
  make ,
  
}
/* react Not a pure module */
