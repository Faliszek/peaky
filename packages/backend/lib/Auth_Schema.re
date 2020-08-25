// let auth: Graphql_lwt.Schema.typ(Hmap.t, option(Auth.Api.t)) =
//   Graphql_lwt.Schema.(
//     obj("user", ~doc="A user in the system", ~fields=_ =>
//       [
//         field(
//           "id",
//           ~typ=non_null(string),
//           ~args=Arg.[],
//           ~resolve=(info, p: User.Api.t) =>
//           p.id
//         ),
//         field(
//           "email",
//           ~typ=non_null(string),
//           ~args=Arg.[],
//           ~resolve=(info, p: User.Api.t) =>
//           p.email
//         ),
//         field(
//           "archived",
//           ~typ=non_null(bool),
//           ~args=Arg.[],
//           ~resolve=(info, p: User.Api.t) =>
//           p.archived
//         ),
//       ]
//     )
//   );
