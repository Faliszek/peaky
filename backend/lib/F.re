module Array = {
  let collect = arr =>
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
  let collect = list =>
    list
    |> List.fold_left(
         (acc, a) =>
           switch (a) {
           | Some(a) => List.concat([acc, [a]])
           | None => []
           },
         [],
       );

  let headOption = list => List.nth_opt(list, 0);
};

module Option = {};