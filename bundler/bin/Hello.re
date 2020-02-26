open Lib;
let time = f => {
  let t = Sys.time();
  f();
  let s = Sys.time() -. t;
  let ms = s *. 1_000.0;

  ms |> string_of_float |> Messages.Info.executionTime |> App.log;
};

let () = time(Util.main);