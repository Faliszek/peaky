let getAll = () => {
  Db.connect()
  |> Lwt.bind(_, Pgx_lwt.execute(_, "select * from p_users"))
  |> Lwt.map(users => users |> List.map(User.Db.toApi) |> F.List.flatten);
};

let get = (~id) =>
  switch (int_of_string(id)) {
  | exception e => Lwt.return(None)
  | id =>
    Db.connect()
    |> Lwt.bind(
         _,
         Pgx_lwt.execute(
           _,
           ~params=[Pgx_value.of_int(id)],
           "select * from p_users where id=$1",
         ),
       )
    |> Lwt.map(users => users |> List.map(User.Db.toApi))
    |> Lwt.map(users =>
         users |> F.List.headOption |> Option.value(~default=None)
       )
  };