let user: Graphql_lwt.Schema.typ(Hmap.t, option(User.Api.t)) =
  Graphql_lwt.Schema.(
    obj("user", ~doc="A user in the system", ~fields=_ =>
      [
        field(
          "id",
          ~typ=non_null(string),
          ~args=Arg.[],
          ~resolve=(info, p: User.Api.t) =>
          p.id
        ),
        field(
          "email",
          ~typ=non_null(string),
          ~args=Arg.[],
          ~resolve=(info, p: User.Api.t) =>
          p.email
        ),
        field(
          "archived",
          ~typ=non_null(bool),
          ~args=Arg.[],
          ~resolve=(info, p: User.Api.t) =>
          p.archived
        ),
      ]
    )
  );

let mutations =
  Graphql_lwt.Schema.[
    io_field(
      "signUp",
      ~typ=user,
      ~args=
        Arg.[
          arg("email", non_null(string)),
          arg("password", non_null(string)),
        ],
      ~resolve=(_info, (), email, password) => {
      Users_Api.create(~email, ~password) |> Lwt_result.ok
    }),
    io_field(
      "archiveUser",
      ~typ=user,
      ~args=Arg.[arg("id", non_null(string))],
      ~resolve=(_info, (), id) => {
      Users_Api.archive(~id) |> Lwt_result.ok
    }),
    io_field(
      "restoreUser",
      ~typ=user,
      ~args=Arg.[arg("id", non_null(string))],
      ~resolve=(_info, (), id) => {
      Users_Api.restore(~id) |> Lwt_result.ok
    }),
  ];

let query =
  Graphql_lwt.Schema.[
    io_field(
      "users",
      ~typ=non_null(list(non_null(user))),
      ~args=[],
      ~resolve=(_info, ()) => {
      Users_Api.getAll() |> Lwt_result.ok
    }),
    io_field(
      "user",
      ~typ=user,
      ~args=Arg.[arg("id", non_null(string))],
      ~resolve=(_, _, id) => {
      Users_Api.getOne(~id) |> Lwt_result.ok
    }),
  ];
