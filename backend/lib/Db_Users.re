open User;

let getAll = () => {
  Unix.sleep(5);

  Pgx_lwt.connect(
    ~database="pawelfalisz",
    ~user="pawelfalisz",
    ~verbose=1,
    (),
  )
  |> Lwt.bind(_, Pgx_lwt.execute(_, "select * from p_users"))
  |> Lwt.map(users => users |> List.map(User.Db.toApi) |> F.List.flatten);
};