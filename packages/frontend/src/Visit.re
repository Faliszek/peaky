type call = {
  id: string,
  duration: float,
  timestamp: string,
  answered: bool,
};

let calls = [|
  {
    id: "1",
    duration: 3_600_000.0,
    timestamp: Time.nowMs()->Js.Float.toString,
    answered: true,
  },
  {
    id: "2",
    duration: 3_600_000.0,
    timestamp: Time.nowMs()->Js.Float.toString,
    answered: false,
  },
|];
