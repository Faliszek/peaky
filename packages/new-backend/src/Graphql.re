type schema;

type payload;

type info;
type request = {
  headers: option(Js.t({. "Authorization": option(string)})),
};

type context = Graphql_Context.t;

type res('a) = Promise.rejectable('a, Js.Promise.error);

type root = {
  quoteOfTheDay: unit => string,
  random: unit => float,
  hello: unit => string,
  signIn: (Graphql_Auth.payload, Graphql_Context.t) => res(option(string)),
  signUp:
    (Graphql_Auth.payload, Graphql_Context.t) =>
    res(option(Firebase.Auth.User.t)),
};

type graphQlConfig = {
  graphiql: bool,
  schema,
  rootValue: root,
  context: Graphql_Context.t,
};

[@bs.module "express-graphql"]
external make: graphQlConfig => Express.Middleware.t = "graphqlHTTP";

[@bs.module "graphql"] external build: string => schema = "buildSchema";

let root: root = {
  quoteOfTheDay: () =>
    Js.Math.random() < 0.5 ? "Take it easy" : "Salvation lies within",

  random: () => Js.Math.random(),
  hello: () => "Morning!",
  signIn: Graphql_Auth.signIn,
  signUp: Graphql_Auth.signUp,
  // me: User.resolve,
};
