type timeoutID;

[@bs.val] external set: (unit => unit, int) => timeoutID = "setTimeout";

[@bs.val] external clear: timeoutID => unit = "setTimeout";
