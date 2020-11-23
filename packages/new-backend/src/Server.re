%raw
{|
// Set the configuration for your app
  // TODO: Replace with your project's config object

|};

module Path = {
  [@bs.module "path"] external resolve: unit => string = "resolve";
};

let schemaPath = Path.resolve() ++ "/src/schema.graphql";

let schema = schemaPath->File.read("utf8")->Graphql.build;

Firebase.make(Config.default);
Firebase.Database.make();

Express.(
  {
    let app = express();

    app->App.use(Cors.make());
    app->App.useOnPath(
      ~path="/graphql",
      Graphql.(make({schema, graphiql: true, rootValue: root})),
    );

    app->App.listen(~port=4000, ()) |> ignore;
  }
);

Js.log("Running a GraphQL API server at localhost:4000/graphql");
