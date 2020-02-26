open App;
open Messages;

let tryParse = (~path, ~fileName) => {
  fileName
  |> Lwt_io.lines_of_file
  |> Lwt_stream.map(s => Html.parse(s))
  |> Lwt_stream.iter(ignore)
  |> Lwt_main.run;
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