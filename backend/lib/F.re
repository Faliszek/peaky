module Array = {
  let flatten = arr =>
    arr
    |> Array.fold_left(
         (acc, a) =>
           switch (a) {
           | Some(a) => Array.concat([acc, [|a|]])
           | None => [||]
           },
         [||],
       );
};

module List = {
  let flatten = list =>
    list
    |> List.fold_left(
         (acc, a) =>
           switch (a) {
           | Some(a) => List.concat([acc, [a]])
           | None => []
           },
         [],
       );
};