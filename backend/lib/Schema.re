open User.Api;
open Graphql_lwt;

let user =
  Schema.(
    obj("user", ~doc="A user in the system", ~fields=_ =>
      [
        field("id", ~typ=non_null(string), ~args=Arg.[], ~resolve=(info, p) =>
          p.id
        ),
        field(
          "email", ~typ=non_null(string), ~args=Arg.[], ~resolve=(info, p) =>
          p.email
        ),
      ]
    )
  );

let schema: Schema.schema(Hmap.t) =
  Schema.(
    schema(
      ~mutations=[
        io_field(
          "register",
          ~typ=user,
          ~args=
            Arg.[
              arg("email", non_null(string)),
              arg("password", non_null(string)),
            ],
          ~resolve=(_info, (), email, password) => {
          Db_Users.create(~email, ~password) |> Lwt_result.ok
        }),
      ],
      [
        io_field(
          "documents",
          ~typ=non_null(list(non_null(user))),
          ~args=Arg.[],
          ~resolve=(_info, ()) => {
          [] |> Lwt.return |> Lwt_result.ok
        }),
        io_field(
          "users",
          ~typ=non_null(list(non_null(user))),
          ~args=[],
          ~resolve=(_info, ()) => {
          Db_Users.getAll() |> Lwt_result.ok
        }),
        io_field(
          "user",
          ~typ=user,
          ~args=Arg.[arg("id", non_null(string))],
          ~resolve=(_, _, id) => {
          Db_Users.get(~id) |> Lwt_result.ok
        }),
      ],
    )
  );