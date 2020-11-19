type schema;

module Cors = {
  [@bs.module] external make: unit => Express.Middleware.t = "cors";
};

module File = {
  [@bs.module "fs"] external read: (string, string) => string = "readFileSync";
};

module Graphql = {
  type root = {
    quoteOfTheDay: unit => string,
    random: unit => float,
    hello: unit => string,
  };

  type args = {
    graphiql: bool,
    schema,
    rootValue: root,
  };
  [@bs.module "express-graphql"]
  external make: args => Express.Middleware.t = "graphqlHTTP";

  [@bs.module "graphql"] external build: string => schema = "buildSchema";
};

module Path = {
  [@bs.module "path"] external resolve: unit => string = "resolve";
};

let root: Graphql.root = {
  quoteOfTheDay: () =>
    Js.Math.random() < 0.5 ? "Take it easy" : "Salvation lies within",
  random: () => Js.Math.random(),
  hello: () => "Morning!",
};

let schemaPath = Path.resolve() ++ "/src/schema.graphql";

let schema = schemaPath->File.read("utf8")->Graphql.build;

Express.(
  {
    let app = express();

    app->App.use(Cors.make());
    app->App.useOnPath(
      ~path="/graphql",
      Graphql.make({schema, graphiql: true, rootValue: root}),
    );

    app->App.listen(~port=4000, ()) |> ignore;
  }
);

Js.log("Running a GraphQL API server at localhost:4000/graphql");
