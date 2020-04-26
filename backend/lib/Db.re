let connect = () =>
  Pgx_lwt.connect(~database="pawelfalisz", ~user="pawelfalisz", ());