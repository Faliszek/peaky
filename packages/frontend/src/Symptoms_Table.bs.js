

import * as Cn from "re-classnames/src/Cn.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as ReactFeather from "react-feather";

function Symptoms_Table$SymptomRow$Label(Props) {
  var label = Props.label;
  var value = Props.value;
  return React.createElement("div", {
              className: "px-2 py-3 text-gray-500 flex border border-gray-50"
            }, React.createElement("div", {
                  className: "flex-1 text-md"
                }, React.createElement(Text$Peaky.make, {
                      children: label
                    }), React.createElement(Text$Peaky.make, {
                      children: " : "
                    })), React.createElement("div", {
                  className: "flex-1"
                }, React.createElement(Text$Peaky.make, {
                      children: value === "" ? "-" : value
                    })));
}

var Label = {
  make: Symptoms_Table$SymptomRow$Label
};

function Symptoms_Table$SymptomRow(Props) {
  var name = Props.name;
  var index = Props.index;
  var circumstances = Props.circumstances;
  var occurences = Props.occurences;
  var description = Props.description;
  var causedBy = Props.causedBy;
  var notes = Props.notes;
  var date = Props.date;
  var match = React.useState(function () {
        return true;
      });
  var setExpanded = match[1];
  var expanded = match[0];
  var rotated = expanded ? "rotate-180" : "rotate-0";
  var toggled = expanded ? "scale-y-100 max-h-full" : "scale-y-0 max-h-0";
  var index$1 = (index + 1 | 0).toString() + ") ";
  return React.createElement("li", {
              className: "px-4 py-5 mb-4 rounded-lg border-gray-200 border text-xl"
            }, React.createElement("div", {
                  className: "flex justify-between cursor-pointer",
                  onClick: (function (param) {
                      return Curry._1(setExpanded, (function (v) {
                                    return !v;
                                  }));
                    })
                }, React.createElement("span", {
                      className: "text-2xl text-gray-500"
                    }, React.createElement(Text$Peaky.make, {
                          children: index$1 + name
                        })), React.createElement(ReactFeather.ChevronDown, {
                      size: "36",
                      className: Cn.$plus("transition transition-transform transform", rotated)
                    })), React.createElement("div", {
                  className: Cn.$plus("h-full transition transition-transform transform origin-top rounded-md overflow-hidden mx-6", toggled)
                }, React.createElement("div", {
                      className: "h-6"
                    }), React.createElement(Symptoms_Table$SymptomRow$Label, {
                      label: "Okoliczności pojawienia się",
                      value: circumstances
                    }), React.createElement(Symptoms_Table$SymptomRow$Label, {
                      label: "Data pierwszego wystąpienia",
                      value: date
                    }), React.createElement(Symptoms_Table$SymptomRow$Label, {
                      label: "Częstotliwość występowania",
                      value: occurences
                    }), React.createElement(Symptoms_Table$SymptomRow$Label, {
                      label: "Opis",
                      value: description
                    }), React.createElement(Symptoms_Table$SymptomRow$Label, {
                      label: "Spowodowany przez",
                      value: causedBy
                    }), React.createElement(Symptoms_Table$SymptomRow$Label, {
                      label: "Dodatkowe informacje",
                      value: notes
                    })));
}

var SymptomRow = {
  Label: Label,
  make: Symptoms_Table$SymptomRow
};

function Symptoms_Table(Props) {
  var symptoms = Props.symptoms;
  return React.createElement("ol", undefined, Belt_Array.mapWithIndex(symptoms, (function (index, s) {
                    return React.createElement(Symptoms_Table$SymptomRow, {
                                name: s.name,
                                index: index,
                                circumstances: s.circumstances,
                                occurences: s.occurences,
                                description: s.description,
                                causedBy: s.causedBy,
                                notes: s.notes,
                                date: s.date,
                                key: s.id
                              });
                  })));
}

var make = Symptoms_Table;

export {
  SymptomRow ,
  make ,
  
}
/* react Not a pure module */
