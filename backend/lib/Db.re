open Postgresql;

Fmt_tty.setup_std_outputs();
Logs.set_level(Some(Logs.Info));
Logs.set_reporter(Logs_fmt.reporter());

module Error = {
  let connectionErr =
    <Pastel>
      <Pastel color=Pastel.RedBright> "Error: " </Pastel>
      "While trying to connect with "
      <Pastel bold=true> "PostgreSQL" </Pastel>
      ", are you sure database is installed and running?\n"
    </Pastel>;

  let printAndAbort = exn => {
    Logs.err(m => m("Connection failure \n"));

    Console.error(connectionErr);
    Console.error(exn);
    exit(1);
  };
};

let intToFileDescriptor = Obj.magic;

let wait_for_result = c => {
  c#consume_input;
  while (c#is_busy) {
    ignore(Unix.select([Obj.magic(c#socket)], [], [], -1.0));
    c#consume_input;
  };
};

let fetch_result = c => {
  wait_for_result(c);
  c#get_result;
};

let fetch_single_result = c =>
  switch (fetch_result(c)) {
  | None => assert(false)
  | Some(r) =>
    assert(fetch_result(c) == None);
    r;
  };

/* See http://www.postgresql.org/docs/devel/static/libpq-connect.html */
let rec finishConnection = (~socket, ~connectPoll, ~connectPolState) =>
  switch (connectPolState) {
  | Polling_failed =>
    Logs.err(m => m("Error while connection database: Pooling failed!"))
  | Polling_reading =>
    Logs.debug(m => m("Reading!"));
    Unix.select([socket], [], [], -1.0) |> ignore;
    finishConnection(~socket, ~connectPoll, ~connectPolState=connectPoll());
  | Polling_writing =>
    Logs.debug(m => m("Writing!"));
    Unix.select([], [socket], [], -1.0) |> ignore;
    finishConnection(~socket, ~connectPoll, ~connectPolState=connectPoll());
  | Polling_ok => Logs.debug(m => m("Pooling ok!"))
  };

let test = (c: connection) => {
  /* Create a table using a non-prepared statement. */
  c#send_query(
    "CREATE TABLE IF NOT EXISTS ocaml_async (id SERIAL PRIMARY KEY, a INTEGER NOT NULL, b TEXT NOT NULL)",
  );
  assert(fetch_single_result(c)#status == Command_ok);

  /* Populate using a prepared statement. */
  c#send_prepare(
    "test_ins",
    "INSERT INTO ocaml_async (a, b) VALUES ($1, $2)",
  );
  assert(fetch_single_result(c)#status == Command_ok);
  c#send_query_prepared(~params=[|"8", "eight"|], "test_ins");
  assert(fetch_single_result(c)#status == Command_ok);
  // /* Prepare a select statement. */
  // c#send_prepare("test_sel", "SELECT * FROM ocaml_async");
  // assert(fetch_single_result(c)#status == Command_ok);
  // /* Describe it. */
  // c#send_describe_prepared("test_sel");
  // let r = fetch_single_result(c);
  // assert(r#status == Command_ok);
  // assert(r#nfields == 3);
  // assert(r#fname(0) == "id");
  // assert(r#fname(1) == "a");
  // assert(r#fname(2) == "b");
  // /* Run it. */
  // c#send_query_prepared("test_sel");
  // let r = fetch_single_result(c);
  // print_endline(r#ntuples |> string_of_int);
  // assert(r#status == Tuples_ok);
  // assert(r#nfields == 3);
  // /* Run it in single-row mode. */
  // c#send_query_prepared("test_sel");
  // c#set_single_row_mode;
  // assert(fetch_result(c) == None);
};

let run = () => {
  /* Async connect and test. */
  let c = (new connection)(~startonly=true, ());
  let socket = c#socket |> intToFileDescriptor;

  c#set_nonblocking(true);

  switch (c#status) {
  | Ok => Logs.info(m => m("Connection succeed"))
  | Connection_started => Logs.info(m => m("Connection started"))
  | Connection_made => Logs.info(m => m("Connection made, database is ready"))
  | Connection_awaiting_response => Logs.info(m => m("Connection awaiting"))
  | Connection_auth_ok =>
    Logs.info(m => m("Authentication with postgres succeed"))
  | Connection_setenv => Logs.info(m => m("Setting required envs"))
  | Connection_ssl_startup =>
    Logs.info(m => m("Setting up secure connection with postgress"))
  | Bad => Error.printAndAbort(c#error_message)
  };

  finishConnection(socket, () => c#connect_poll, Polling_writing);

  assert(c#status == Ok);
  test(c);
  // /* Async reset and test again. */
  // if (!c#reset_start) {
  //   failwith_f("reset_start failed: %s", c#error_message);
  // };
  // finishConnection(Obj.magic(c#socket), () => c#reset_poll, Polling_writing);
  // if (c#status == Bad) {
  //   failwith_f("Reset connection bad: %s", c#error_message);
  // };
  // assert(c#status == Ok);
  // test(c);
};

let init = () => {
  Logs.info(m => m("Connecting to database"));

  try(run()) {
  | Postgresql.Error(exn) =>
    exn |> Postgresql.string_of_error |> Error.printAndAbort
  | exn => exn |> Printexc.to_string |> Error.printAndAbort
  };
};