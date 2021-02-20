type t = {
  id: string,
  duration: float,
  timestamp: float,
  answered: bool,
  withWho: option<string>,
}

let fromGraphql = (~id, ~duration, ~timestamp, ~answered, ~withWho=?, ()): t => {
  id: id,
  duration: duration,
  timestamp: timestamp,
  answered: answered,
  withWho: withWho,
}
