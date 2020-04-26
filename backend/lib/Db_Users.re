let table = {j|p_users|j};

let getAll = () => {
  Db.query("select * from p_users")
  |> Lwt.map(users => users |> List.map(User.Db.toApi) |> F.List.flatten);
};

let get = (~id) =>
  switch (int_of_string(id)) {
  | exception e => Lwt.return(None)
  | id =>
    Db.query(
      ~params=[Pgx_value.of_int(id)],
      "select * from p_users where id=$1",
    )
    |> Lwt.map(users => users |> List.map(User.Db.toApi))
    |> Lwt.map(users =>
         users |> F.List.headOption |> Option.value(~default=None)
       )
  };

let create = (~email, ~password) => {
  switch (email, password) {
  | (email, password) =>
    Db.query(
      ~params=[Pgx_value.of_string(email), Pgx_value.of_string(password)],
    )
  };
};