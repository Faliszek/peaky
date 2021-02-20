

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Call$Peaky from "./Call.bs.js";
import * as Page$Peaky from "./components/Page.bs.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Spinner$Peaky from "./components/Spinner.bs.js";
import * as ReactFeather from "react-feather";
import * as Calls_Query$Peaky from "./Calls_Query.bs.js";
import * as Visits_History$Peaky from "./Visits_History.bs.js";

function withWho(from_, to_, myId) {
  if (from_.id !== myId) {
    return from_.firstName + (" " + from_.lastName);
  } else if (to_.id !== myId) {
    return to_.firstName + (" " + to_.lastName);
  } else {
    return ;
  }
}

function Calls_List_View(Props) {
  var callModeOpt = Props.callMode;
  var callMode = callModeOpt !== undefined ? callModeOpt : false;
  var match = Curry.app(Calls_Query$Peaky.Query.useLazy, [
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined
      ]);
  var queryCalls = match[1];
  var executeQuery = match[0];
  React.useEffect((function () {
          Curry._3(executeQuery, undefined, undefined, undefined);
          
        }), []);
  var tmp;
  if (queryCalls.TAG === /* Executed */0) {
    var match$1 = queryCalls._0;
    var match$2 = match$1.data;
    if (match$1.loading) {
      tmp = React.createElement(Spinner$Peaky.make, {});
    } else if (match$2 !== undefined) {
      var me = match$2.me;
      var calls = Belt_Array.map(match$2.calls, (function (c) {
              return Call$Peaky.fromGraphql(c.id, c.duration, c.timestamp, c.answered, withWho(c.from_, c.to_, me.id), undefined);
            }));
      tmp = React.createElement(Visits_History$Peaky.make, {
            calls: calls,
            callMode: callMode
          });
    } else {
      tmp = null;
    }
  } else {
    tmp = null;
  }
  return React.createElement(Page$Peaky.make, {
              title: "Wizyty",
              children: tmp,
              actions: React.createElement(Button$Peaky.CTA.make, {
                    children: React.createElement(Text$Peaky.make, {
                          children: "Odśwież listę"
                        }),
                    icon: React.createElement(ReactFeather.RefreshCcw, {
                          className: "mr-4"
                        }),
                    onClick: (function (param) {
                        return Curry._3(executeQuery, undefined, undefined, undefined);
                      })
                  })
            });
}

var make = Calls_List_View;

export {
  withWho ,
  make ,
  
}
/* react Not a pure module */
