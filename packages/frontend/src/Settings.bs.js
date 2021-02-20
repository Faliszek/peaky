

import * as React from "react";
import * as Page$Peaky from "./components/Page.bs.js";

function Settings(Props) {
  return React.createElement(Page$Peaky.make, {
              title: "Ustawienia",
              children: "Some content"
            });
}

var make = Settings;

export {
  make ,
  
}
/* react Not a pure module */
