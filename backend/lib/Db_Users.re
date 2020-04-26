let table = {j|p_users|j};

let getAll = () => {
  Db.query("select * from p_users")
  |> Lwt.map(users => users |> List.map(User.toApi) |> F.List.collect);
};

let get = (~id) =>
  switch (int_of_string(id)) {
  | exception e => Lwt.return(None)
  | id =>
    Db.query(
      ~params=[Pgx_value.of_int(id)],
      "select * from p_users where id=$1",
    )
    |> Lwt.map(users => users |> List.map(User.toApi))
    |> Lwt.map(users =>
         users |> F.List.headOption |> Option.value(~default=None)
       )
  };

let create = (~email, ~password) =>
  User.Api.(
    {
      switch (email, password) {
      | (email, password) =>
        Db.query(
          ~params=[
            Pgx_value.of_string(email),
            Pgx_value.of_string(password),
          ],
          "insert into p_users (email, password) values($1, $2) RETURNING id",
        )
        |> Lwt.map(result => {
             result
             |> List.flatten
             |> F.List.headOption
             |> Option.bind(_, Pgx.Value.to_string)
             |> Option.map(id => {id, email})
           })
      };
    }
  );