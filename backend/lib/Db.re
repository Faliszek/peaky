// open Postgresql;

// Fmt_tty.setup_std_outputs();
// Logs.set_level(Some(Logs.Info));
// Logs.set_reporter(Logs_fmt.reporter());

// module Error = {
//   let printAndAbort = (type_, exn) => {
//     switch (type_) {
//     | `Postgresql => Logs.err(m => m("PostrgreSQL error"))
//     | `System => Logs.err(m => m("Unexpected error"))
//     };

//     Console.error(
//       <Pastel>
//         <Pastel bold=true color=Pastel.Red> "ERROR! " </Pastel>
//         exn
//       </Pastel>,
//     );
//   };
// };

// let connection: ref(option(connection)) = ref(None);

// let getConnection = () => {
//   let c = connection^;
//   c;
// };

// let intToFileDescriptor = Obj.magic;

// let waitForResult = c => {
//   c#consume_input;
//   while (c#is_busy) {
//     Unix.select([Obj.magic(c#socket)], [], [], -1.0) |> ignore;
//     print_endline("consuming");
//     c#consume_input;
//   };
// };

// let fetchResult = c => {
//   switch (c) {
//   | Some(c) =>
//     waitForResult(c);
//     print_endline("Consuming ended");
//     c#get_result;
//   | None =>
//     print_endline("Error while fetching, no connection found");
//     None;
//   };
// };

// /* See http://www.postgresql.org/docs/devel/static/libpq-connect.html */
// let rec finishConnection = (~connectPolState) => {
//   let connection = getConnection();

//   switch (connection, connectPolState) {
//   | (Some(connection), Polling_failed) =>
//     Logs.err(m => m("Error while connection database: Pooling failed!"))
//   | (Some(connection), Polling_reading) =>
//     Logs.info(m => m("Reading!"));
//     let connectPoll = () => connection#connect_poll;
//     Unix.select([Obj.magic(connection#socket)], [], [], -1.0) |> ignore;
//     finishConnection(~connectPolState=connectPoll());
//   | (Some(connection), Polling_writing) =>
//     Logs.info(m => m("Writing!"));
//     let connectPoll = () => connection#connect_poll;
//     Unix.select([], [Obj.magic(connection#socket)], [], -1.0) |> ignore;
//     finishConnection(~connectPolState=connectPoll());

//   | (Some(connection), Polling_ok) => Logs.debug(m => m("Pooling ok!"))
//   | (None, _) => Logs.err(m => m("None connection avaiable when pooling"))
//   };
// };

// let fetch = (~f) => {
//   /* Create a table using a non-prepared statement. */
//   // c#send_query(
//   //   "CREATE TABLE IF NOT EXISTS ocaml_async (id SERIAL PRIMARY KEY, a INTEGER NOT NULL, b TEXT NOT NULL)",
//   // );

//   // let id = "1";

//   /* Populate using a prepared statement. */
//   let result = fetchResult(connection^);

//   switch (result) {
//   | None => ()
//   | Some(result) =>
//     switch (result#status) {
//     //insert / delete
//     | Command_ok => Logs.info(m => m("Command ok"))
//     //select empty query
//     | Empty_query => Logs.info(m => m("Empty_query"))
//     //select success with data
//     | Tuples_ok =>
//       let data = result#get_all;
//       f(data);
//       Logs.info(m => m("Tuples_ok"));
//     | Copy_out => Logs.info(m => m("Copy_out"))
//     | Copy_in => Logs.info(m => m("Copy in"))

//     | Copy_both => Logs.info(m => m("Copy_both"))
//     | Single_tuple => Logs.info(m => m("Single_tuple"))

//     | Bad_response => Logs.err(m => m("Bad_response"))
//     | Nonfatal_error =>
//       // let err = c#error_message;
//       print_endline("Posgtres error ")

//     | Fatal_error => Logs.err(m => m("Fatal_error"))
//     // print_endline(err);
//     }
//   };
//   // c#send_query_prepared(
//   //   ~params=[|"8", "eight"|],
//   //   "INSERT INTO ocaml_async (a, b) VALUES ($1, $2)",
//   // );
//   // assert(fetch_single_result(c)#status == Command_ok);
//   // /* Prepare a select statement. */r
//   // c#send_prepare("test_sel", "SELECT * FROM ocaml_async");
//   // assert(fetch_single_result(c)#status == Command_ok);
//   // /* Describe it. */
//   // c#send_describe_prepared("test_sel");
//   // let r = fetch_single_result(c);
//   // assert(r#status == Command_ok);
//   // assert(r#nfields == 3);
//   // assert(r#fname(0) == "id");
//   // assert(r#fname(1) == "a");
//   // assert(r#fname(2) == "b");
//   // /* Run it. */
//   // c#send_query_prepared("test_sel");
//   // let r = fetch_single_result(c);
//   // print_endline(r#ntuples |> string_of_int);
//   // assert(r#status == Tuples_ok);
//   // assert(r#nfields == 3);
//   // /* Run it in single-row mode. */
//   // c#send_query_prepared("test_sel");
//   // c#set_single_row_mode;
//   // assert(fetch_result(c) == None);
// };

// // type queryType =
// //   | Raw
// //   | Create
// //   | Delete
// //   | Insert
// //   | Select
// //   | InsertOne
// //   | SelectOne;

// let run = () => {
//   /* Async connect and test. */
//   let c = (new connection)(~startonly=true, ());

//   c#set_nonblocking(true);

//   switch (c#status) {
//   | Ok => Logs.info(m => m("Connection succeed"))
//   | Connection_started => Logs.info(m => m("Connection started"))
//   | Connection_made =>
//     Logs.info(m => m("Connection made, database is ready"));

//     connection := Some(c);
//   | Connection_awaiting_response => Logs.info(m => m("Connection awaiting"))
//   | Connection_auth_ok =>
//     Logs.info(m => m("Authentication with postgres succeed"))
//   | Connection_setenv => Logs.info(m => m("Setting required envs"))
//   | Connection_ssl_startup =>
//     Logs.info(m => m("Setting up secure connection with postgress"))
//   | Bad => Error.printAndAbort(`Postgresql, c#error_message)
//   };

//   finishConnection(Polling_writing);
//   // test(c);
//   // /* Async reset and test again. */
//   // if (!c#reset_start) {
//   //   failwith_f("reset_start failed: %s", c#error_message);
//   // };
//   // finishConnection(Obj.magic(c#socket), () => c#reset_poll, Polling_writing);
//   // if (c#status == Bad) {
//   //   failwith_f("Reset connection bad: %s", c#error_message);
//   // };
//   // assert(c#status == Ok);
//   // test(c);
// };

// let handleDBQuery = f => {
//   try(f()) {
//   | Postgresql.Error(Field_out_of_range(x, y)) => print_endline("Binary")
//   | Postgresql.Error(Tuple_out_of_range(x, y)) =>
//     print_endline("Tuple_out_of_range")
//   | Postgresql.Error(Binary) => print_endline("Binary")
//   | Postgresql.Error(Unexpected_status(result, e, y)) =>
//     print_endline("Unexpected status: " ++ e)
//   | Postgresql.Error(Connection_failure(e)) =>
//     print_endline("Connection_failure: " ++ e)
//   | Postgresql.Error(Cancel_failure(reason)) =>
//     print_endline("Cancel_failure: " ++ reason)

//   | exn =>
//     print_endline("BANG!!!");
//     exn |> Printexc.to_string |> Error.printAndAbort(`System);
//   };

//   finishConnection(Polling_writing);
// };

// let init = () => {
//   Logs.info(m => m("Connecting to database"));
//   handleDBQuery(run);
// };