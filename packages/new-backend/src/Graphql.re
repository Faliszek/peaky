type schema;

type root = {
  quoteOfTheDay: unit => string,
  random: unit => float,
  hello: unit => string,
  signIn: Auth.payload => string,
};

type args = {
  graphiql: bool,
  schema,
  rootValue: root,
};
[@bs.module "express-graphql"]
external make: args => Express.Middleware.t = "graphqlHTTP";

[@bs.module "graphql"] external build: string => schema = "buildSchema";

let root: root = {
  quoteOfTheDay: () =>
    Js.Math.random() < 0.5 ? "Take it easy" : "Salvation lies within",

  random: () => Js.Math.random(),
  hello: () => "Morning!",
  signIn: Auth.signIn,
};
