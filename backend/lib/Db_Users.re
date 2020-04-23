open Db_Schema.User;

// let getAll = () => {
//   Db.getConnection()
//   |> Option.bind(
//        _,
//        connection => {
//          //  print_endline("sending query");
//          let a = () => connection#send_query("select * from p_users");
//          Db.handleDBQuery(a);

//          Db.fetchResult(Some(connection));
//        },
//      )
//   |> Option.map(result => {
//        print_endline("fetching result done");

//        result#get_all
//        |> Array.map(row => {
//             switch (row) {
//             | [|id, email, password|] => Some({id, email, password})
//             | _ => None
//             }
//           })
//        |> F.Array.flatten;
//      });
// };

let func = (~column_names, ~values) => {
  column_names |> Array.map(a => print_endline(a)) |> ignore;
  values |> Array.map(a => a |> Option.map(print_endline)) |> ignore;
};

// let query: unit => Lwt.t('a) = Obj.magic(Postgres_async.query);

// * |> Option.value(~default=[])*/;
// } /*  Postgres_async.query*/;

//    p,
//    ~parameters=[||],
//    ~handle_row=func,
//    "select * from p_users",
//  )
//        p,
//        ~parameters=[||],
//        ~handle_row=func,
//        "select * from p_users",
//      )
//    )
// |> Async.Deferred.ok
// |> Async.Deferred.map(~f=a =>
//      switch (a) {
//      | Ok(res) => print_endline("ok")
//      | Error(err) => print_endline("err")
//      }
//    )
// |> Async.Deferred.peek
// |> Option.map(~f=a => [])
// |> Async.Deferred.Or_error.bind(~f=p =>
//      Postgres_async.query(
// let connect = Postgres_async.connect(~database="pawelfalisz=#", ());

open Lwt;

let getAll = () => {
  Pgx_lwt.connect()
  >>= (p => p |> Pgx_lwt.execute(_, "select * from p_users"))
  >|= (
    users =>
      users
      |> List.map(u =>
           switch (u) {
           | [email, _] => Pgx_value.to_string(email)
           | _ => None
           }
         )
  )
  >|= (
    s =>
      s
      |> List.map(s =>
           {
             id: s |> Option.value(~default=""),
             email: s |> Option.value(~default=""),
           }
         )
  );
};