

import * as Time$Peaky from "./bindings/Time.bs.js";

var calls = [
  {
    id: "1",
    duration: 3600000.0,
    timestamp: Time$Peaky.nowMs(undefined).toString(),
    answered: true
  },
  {
    id: "2",
    duration: 3600000.0,
    timestamp: Time$Peaky.nowMs(undefined).toString(),
    answered: false
  }
];

export {
  calls ,
  
}
/* calls Not a pure module */
