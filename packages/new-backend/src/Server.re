let schemaPath = Path.resolve() ++ "/src/schema.graphql";

let schema = schemaPath->File.read("utf8")->Graphql.build;

let app = Firebase.initializeApp(~options=Config.default);

let auth = app->Firebase.auth;
let database = app->Firebase.database;

// var fs = require('fs');
// var http = require('http');
// var https = require('https');

type credentials = {
  key: string,
  cert: string,
};
let privateKey = File.read("src/key.pem", "utf8");
let certificate = File.read("src/cert.pem", "utf8");

let credentials = {key: privateKey, cert: certificate};

type peerOptions = {
  debug: bool,
  path: string,
};

type peerServer = Express.Middleware.t;

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

module Peer = {
  [@bs.module "peer"]
  external make: (Express.HttpServer.t, peerOptions) => peerServer =
    "ExpressPeerServer";
};

Express.(
  {
    let app = express();
    app->App.use(Cors.make());

    let server = app->App.listen(~port=9000, ());
    let peerServer = Peer.make(server, {path: "/", debug: true});
    app->App.useOnPath(~path="/calls", peerServer);
  }
);
Js.log("Running a GraphQL API server at localhost:4000/graphql");
Js.log("Running a Peer server at localhost:9000/calls");
