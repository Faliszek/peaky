type attr = {
  name: string,
  value: string,
};

type token =
  | LeftAngleBracket
  | RightAngleBracket
  | Dash
  | ExclamationMark
  | ClosingSlash
  | Attribute(attr);

type el =
  | Node(array(attr))
  | Comment(string);

let parse = str => print_endline(str);