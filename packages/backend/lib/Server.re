Fmt_tty.setup_std_outputs();
Logs.set_level(Some(Logs.Info));
Logs.set_reporter(Logs_fmt.reporter());

let schema: Graphql_lwt.Schema.schema(Hmap.t) =
  Graphql_lwt.Schema.(
    schema(
      ~mutations=[] @ Users_Schema.mutations @ Auth_Api.mutations,
      Users_Schema.query,
    )
  );

let graphql_handler = Morph_graphql_server.make(schema);

let graphiql_handler = _ => Morph.Response.html(GraphiQL.html) |> Lwt.return;

let getRoutes =
  Routes.[
    empty @--> (_ => Morph.Response.text("Hello world!") |> Lwt.return),
    s("graphql") /? nil @--> graphiql_handler,
  ];

let postRoutes = Routes.[s("graphql") /? nil @--> graphql_handler];

let port =
  switch (Sys.getenv_opt("PORT")) {
  | Some(p) => int_of_string(p)
  | None => 5050
  };

let http_server =
  Morph.Server.make(~port, ~address=Unix.inet_addr_loopback, ());

let run = () => {
  Mirage_crypto_rng_lwt.initialize();

  Morph.start(
    ~servers=[http_server],
    ~middlewares=[
      Morph.Middlewares.Static.make(~path="public", ~public_path="./public"),
    ],
    Morph.Router.make(~get=getRoutes, ~post=postRoutes, ()),
  )
  |> Lwt_main.run;
};
