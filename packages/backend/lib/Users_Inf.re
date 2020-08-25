let table = {j|p_users|j};

let getAll = () => {
  Db.query("select * from p_users");
};

let getOne = (~id) =>
  switch (int_of_string(id)) {
  | exception e => Lwt.return(None)
  | id =>
    Db.query(
      ~params=[Pgx_value.of_int(id)],
      "select * from p_users where id=$1",
    )
    |> Lwt.map(users => users |> F.List.headOption)
  };

let getByEmail = (~email) =>
  switch (email) {
  | exception e => Lwt.return(None)
  | email =>
    Db.query(
      ~params=[Pgx_value.of_string(email)],
      "select * from p_users where email=$1",
    )
    |> Lwt.map(users => users |> F.List.headOption)
  };

let setArchived = (~id, ~value) => {
  switch (int_of_string(id)) {
  | exception e => Lwt.return(None)
  | id =>
    let id = Pgx_value.of_int(id);
    Db.query(
      ~params=[Pgx_value.of_bool(value), id],
      "UPDATE p_users SET archived=$1 WHERE id=$2 RETURNING *",
    )
    |> Lwt.map(users => {users |> F.List.headOption});
  };
};

let create = (~email, ~password, ~archived=false, ()) =>
  User.Api.(
    {
      switch (email, password, archived) {
      | (email, password, archived) =>
        Db.query(
          ~params=[
            Pgx_value.of_string(email),
            Pgx_value.of_string(password),
            Pgx_value.of_bool(archived),
          ],
          "insert into p_users (email, password) values($1, $2) RETURNING id",
        )
        |> Lwt.map(result => {
             result
             |> List.flatten
             |> F.List.headOption
             |> Option.bind(_, Pgx.Value.to_string)
             |> Option.map(id => {id, email, archived})
           })
      };
    }
  );
