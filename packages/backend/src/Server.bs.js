'use strict';

var Fs = require("fs");
var Cors = require("cors");
var Path = require("path");
var Peer = require("peer");
var Config = require("./Config.bs.js");
var Express = require("bs-express/src/Express.bs.js");
var Graphql = require("./Graphql.bs.js");
var Graphql$1 = require("graphql");
var Firebase = require("firebase");
var SubServer = require("./SubServer.bs.js");
var ExpressGraphql = require("express-graphql");

var schemaPath = Path.resolve() + "/src/schema.graphql";

var schema = Graphql$1.buildSchema(Fs.readFileSync(schemaPath, "utf8"));

var app = Firebase.initializeApp(Config.$$default);

var auth = Firebase.auth(app);

var database = Firebase.database(app);

var privateKey = Fs.readFileSync("src/key.pem", "utf8");

var certificate = Fs.readFileSync("src/cert.pem", "utf8");

var credentials = {
  key: privateKey,
  cert: certificate
};

var SubscrpitionServer = {};

var app$1 = Express.express(undefined);

Express.App.use(app$1, Cors());

Express.App.useOnPath(app$1, "/graphql", ExpressGraphql.graphqlHTTP(function (req) {
          return {
                  graphiql: true,
                  schema: schema,
                  rootValue: Graphql.root,
                  context: {
                    auth: auth,
                    db: database,
                    token: req.headers.authorization
                  }
                };
        }));

SubServer.start(app$1, schema);

Express.App.listen(app$1, 4000, undefined, undefined, undefined);

var Peer$1 = {};

var app$2 = Express.express(undefined);

Express.App.use(app$2, Cors());

var server = Express.App.listen(app$2, 9000, undefined, undefined, undefined);

var peerServer = Peer.ExpressPeerServer(server, {
      debug: true,
      path: "/"
    });

Express.App.useOnPath(app$2, "/calls", peerServer);

console.log("Running a GraphQL API server at localhost:4000/graphql");

console.log("Running a Peer server at localhost:9000/calls");

exports.schemaPath = schemaPath;
exports.schema = schema;
exports.app = app;
exports.auth = auth;
exports.database = database;
exports.privateKey = privateKey;
exports.certificate = certificate;
exports.credentials = credentials;
exports.SubscrpitionServer = SubscrpitionServer;
exports.Peer = Peer$1;
/* schemaPath Not a pure module */
