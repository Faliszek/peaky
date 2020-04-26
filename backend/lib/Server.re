let graphql_handler = Morph_graphql_server.make(Schema.schema);

let handler = (request: Morph.Request.t('a)) => {
  open Morph;

  let path_parts =
    request.target
    |> Uri.of_string
    |> Uri.path
    |> String.split_on_char('/')
    |> List.filter(s => s != "");

  switch (request.meth, path_parts) {
  | (_, []) => Morph.Response.text("Hello world!", Response.empty)
  | (`GET, ["graphql"]) =>
    Morph.Response.text(GraphiQL.html, Morph.Response.empty)
  | (_, ["graphql"]) => graphql_handler(request)
  | (_, _) => Response.not_found(Response.empty)
  };
};

let http_server = Morph_server_http.make(~port=2020, ());

let run = () => {
  Db.connect()
  |> Lwt.on_failure(_, e => print_endline(Printexc.to_string(e)));

  Morph.start(~servers=[http_server], ~middlewares=[Middleware.logger], req =>
    handler(req)
  )
  |> Lwt_main.run;
};