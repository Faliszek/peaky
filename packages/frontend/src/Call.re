type t = {
  id: string,
  duration: float,
  timestamp: float,
  answered: bool,
  withWho: option(string),
};

let fromGraphql = (~id, ~duration, ~timestamp, ~answered, ~withWho=?, ()): t => {
  {id, duration, timestamp, answered, withWho};
};
