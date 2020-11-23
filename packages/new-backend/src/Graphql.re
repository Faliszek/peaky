type schema;

// module User = {
//   type t = {
//     email: string,
//     firstName: string,
//     lastName: string,
//   };

//   let resolve = (payload, request, _, _) => {
//     {
//       email: "pawlic7@gmail.com",
//       firstName: {j|Paweł|j},
//       lastName: {j|Falisz|j},
//     };
//   };
// };

type payload;

type info;
type request = {
  headers: option(Js.t({. "Authorization": option(string)})),
};

type context = Graphql_Context.t;

type root = {
  quoteOfTheDay: unit => string,
  random: unit => float,
  hello: unit => string,
  signIn:
    (Auth.payload, Graphql_Context.t, request, info) =>
    Promise.rejectable(option(string), Promise.never),
  // me: (payload, request, context, info) => User.t,
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
  // me: User.resolve,
};
