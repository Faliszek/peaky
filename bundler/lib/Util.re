open App;
open Messages;

let tryParse = (~path, ~fileName) => {
  // |> Lwt_stream.map(line => Html.parse( line))
  // |> Lwt_stream.iter(ignore)
  Lwt_io.with_file(~mode=Lwt_io.Input, fileName, Lwt_io.read)
  |> Lwt_main.run
  |> Html.parse(~path=path ++ fileName)
  |> ignore;
};

let parseArgs = () =>
  switch (Sys.argv) {
  | [|path, fileName|] =>
    let path = Sys.getcwd() ++ Filename.dir_sep;
    print_endline(path);
    switch (Unix.access(path ++ fileName, [Unix.F_OK])) {
    | file => tryParse(~path, ~fileName)
    | exception exn =>
      Errors.fileNoExist(~path=fileName) |> log;
      exn |> Printexc.to_string |> Errors.sys |> log;
      Errors.getHelp |> log;
    };

  | _ => log(Errors.noFileSpecified)
  };

let main = () => {
  parseArgs();
};