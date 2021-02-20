

import * as DateFns from "date-fns";

function now(param) {
  return new Date();
}

function nowMs(param) {
  return DateFns.getTime(new Date());
}

export {
  now ,
  nowMs ,
  
}
/* date-fns Not a pure module */
