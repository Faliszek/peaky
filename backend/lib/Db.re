type conn = {
  db: string,
  user: string,
};

let conn = {db: "pawelfalisz", user: "pawelfalisz"};

let connect = () => Pgx_lwt.connect(~database=conn.db, ~user=conn.user, ());

let pool: Lwt_pool.t(Pgx_lwt.t) = {
  Lwt_pool.create(16, ~validate=Pgx_lwt.alive, connect);
};

let withPool = connectFunc => Lwt_pool.use(pool, connectFunc);

let query = (~params=?, query: string) =>
  withPool(connection => Pgx_lwt.execute(~params?, connection, query));