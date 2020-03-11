module FCP =
  FileContextPrinter.Make({
    let config =
      FileContextPrinter.Config.initialize({linesBefore: 3, linesAfter: 3});
  });

type attr = {
  name: string,
  value: string,
};

type token =
  | AngleBracketOpen
  | AngleBracketClose
  | Dash
  | ExclamationMark
  | ClosingSlash
  | Attribute(attr);

type el =
  | Node(array(attr))
  | Comment(string);

let parse = (~path, file) => {
  let splitEveryChar = Str.regexp("");
  let chars = Str.split(splitEveryChar, file);
  // FCP.printFile(path, ((7, 1), (7, 11))) |> Option.map(print_endline);

  chars
  |> List.fold_left(
       (acc, char) => {
         print_string(char);
         acc;
       },
       [],
     );
};