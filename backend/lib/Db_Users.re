open User;
open Lwt;

let getAll = () => {
  Pgx_lwt.connect(~database="pawelfalisz", ~user="pawelfalisz", ())
  |> Lwt.bind(_, Pgx_lwt.execute(_, "select * from p_users"))
  |> Lwt.map(users => users |> List.map(User.Db.toApi) |> F.List.flatten);
};