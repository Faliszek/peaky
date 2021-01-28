let schemaPath = Path.resolve() ++ "/src/schema.graphql";

let schema = schemaPath->File.read("utf8")->Graphql.build;

let app = Firebase.initializeApp(~options=Config.default);

let auth = app->Firebase.auth;
let database = app->Firebase.database;

Express.(
  {
    let app = express();
    // req.headers.authorization
    app->App.use(Cors.make());
    app->App.useOnPath(
      ~path="/graphql",
      Graphql.(
        make(req =>
          {
            schema,
            graphiql: true,
            rootValue: root,
            context: {
              auth,
              db: database,
              token: req.headers.authorization,
            },
          }
        )
      ),
    );

    app->App.listen(~port=4000, ()) |> ignore;
  }
);

Js.log("Running a GraphQL API server at localhost:4000/graphql");
