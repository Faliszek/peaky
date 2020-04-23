open Graphql_lwt;
open User;

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
      ~mutations=[], // field(
      //   "addUser",
      //   ~typ=non_null(user),
      //   ~args=
      //     Arg.[
      //       arg("name", non_null(string)),
      //       arg("email", non_null(string)),
      //     ],
      //   ~resolve=(_info, (), name, email) => {
      //     let new_user = {id: List.length(users^) + 1, name, email};
      //     users := [new_user, ...users^];
      //     new_user;
      //   },
      // ),
      [
        field(
          "users",
          ~typ=non_null(list(non_null(user))),
          ~args=Arg.[],
          ~resolve=(_info, ()) =>
          Db_Users.getAll() |> Lwt_main.run
        ),
      ],
    )
  );