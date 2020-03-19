open Printf;
open Postgresql;

let failwith_f = fmt => ksprintf(failwith, fmt);

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
let rec finish_conn = (socket_fd, connect_poll) =>
  fun
  | Polling_failed => printf("f\n%!")
  | Polling_reading => {
      printf("reading,%!");
      ignore(Unix.select([socket_fd], [], [], -1.0));
      finish_conn(socket_fd, connect_poll, connect_poll());
    }
  | Polling_writing => {
      printf("writing,%!");
      ignore(Unix.select([], [socket_fd], [], -1.0));
      finish_conn(socket_fd, connect_poll, connect_poll());
    }
  | Polling_ok => printf("c\n%!");

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

  /* Prepare a select statement. */
  c#send_prepare("test_sel", "SELECT * FROM ocaml_async");
  assert(fetch_single_result(c)#status == Command_ok);

  /* Describe it. */
  c#send_describe_prepared("test_sel");
  let r = fetch_single_result(c);
  assert(r#status == Command_ok);
  assert(r#nfields == 3);
  assert(r#fname(0) == "id");
  assert(r#fname(1) == "a");
  assert(r#fname(2) == "b");

  /* Run it. */
  c#send_query_prepared("test_sel");
  let r = fetch_single_result(c);
  print_endline(r#ntuples |> string_of_int);
  assert(r#status == Tuples_ok);
  assert(r#nfields == 3);

  /* Run it in single-row mode. */
  c#send_query_prepared("test_sel");
  c#set_single_row_mode;

  assert(fetch_result(c) == None);
};

let run = () => {
  /* Async connect and test. */
  let c = (new connection)(~startonly=true, ());
  finish_conn(Obj.magic(c#socket), () => c#connect_poll, Polling_writing);
  if (c#status == Bad) {
    failwith_f("Connection failed: %s", c#error_message);
  };
  assert(c#status == Ok);
  c#set_nonblocking(true);
  test(c);

  /* Async reset and test again. */
  if (!c#reset_start) {
    failwith_f("reset_start failed: %s", c#error_message);
  };
  finish_conn(Obj.magic(c#socket), () => c#reset_poll, Polling_writing);
  if (c#status == Bad) {
    failwith_f("Reset connection bad: %s", c#error_message);
  };
  assert(c#status == Ok);
  test(c);
};