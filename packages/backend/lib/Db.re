type conn = {
  db: string,
  user: string,
};

let conn = {db: "pawelfalisz", user: "pawelfalisz"};

let connect = () =>
  Pgx_lwt_unix.connect(~database=conn.db, ~user=conn.user, ());

let pool: Lwt_pool.t(Pgx_lwt_unix.t) = {
  Lwt_pool.create(16, ~validate=Pgx_lwt_unix.alive, connect);
};

let withPool = connectFunc => Lwt_pool.use(pool, connectFunc);

let query = (~params=?, query: string) => {
  /*  let result = */
  withPool(connection
    => Pgx_lwt_unix.execute(~params?, connection, query));
    /* switch (result) {
        | exception e => Result.Error("Database error: " ++ Printexc.to_string(e))
       | data => Result.Ok(data)
        }; */
};




let queryMany = (~params, ~queries: list(string)) => {
  let query =
    queries |> List.fold_left((acc, query) => acc ++ query ++ ";", "");
  /* let result = */
  withPool(connection =>
    Pgx_lwt_unix.execute_many(~params, ~query, connection)
  );
  /* switch (result) { */
  /* | exception e => Result.Error("Database error: " ++ Printexc.to_string(e)) */
  /* | data => Result.Ok(data) */
  /* }; */
};
