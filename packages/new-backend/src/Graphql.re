type schema;

type payload;

type info;

type context = Graphql_Context.t;

type res('a, 'b) = Promise.rejectable('a, 'b);

type root = {
  signIn:
    (Graphql_Auth.payload, Graphql_Context.t) =>
    res(option(string), Js.Promise.error),
  signUp:
    (Graphql_Auth.payload, Graphql_Context.t) =>
    res(option(Firebase.Auth.User.t), Promise.never),
  createVisit:
    (Api_Visit.createVisitPayload, Graphql_Context.t) =>
    res(option(Domain.Visit.t), Promise.never),
  removeVisit:
    (Api_Visit.removeVisitResponse, Graphql_Context.t) =>
    res(option(Api_Visit.removeVisitResponse), Promise.never),
  createPatient:
    (Api_Patient.createPatientPayload, Graphql_Context.t) =>
    res(option(Domain.Patient.t), Promise.never),
  removePatient:
    (Api_Patient.removePatientResponse, Graphql_Context.t) =>
    res(option(Api_Patient.removePatientResponse), Promise.never),
  me:
    (Api_User.meQueryPayload, Graphql_Context.t) =>
    res(Domain.User.t, Promise.never),
  searchSpecialist:
    (Api_User.searchPayload, Graphql_Context.t) =>
    res(array(Domain.User.t), Promise.never),
  patients:
    (Api_Patient.listPayload, Graphql_Context.t) =>
    res(array(Domain.Patient.t), Promise.never),
  patient:
    (Api_Patient.singlePayload, Graphql_Context.t) =>
    res(array(Domain.Patient.t), Promise.never),
  visits:
    (Api_Visit.listPayload, Graphql_Context.t) =>
    res(array(Domain.Patient.t), Promise.never),
  calls:
    (Api_Call.listPayload, Graphql_Context.t) =>
    res(array(Domain.Call.t), Promise.never),
};

type headers = {authorization: option(string)};
type request = {headers};

type graphQlConfig = {
  graphiql: bool,
  schema,
  rootValue: root,
  context: Graphql_Context.t,
};

let root: root = {
  signIn: Graphql_Auth.signIn,
  signUp: Graphql_Auth.signUp,
  createVisit: Api_Visit.createVisit,
  removeVisit: Api_Visit.remove,
  createPatient: Api_Patient.createPatient,
  removePatient: Api_Patient.removePatient,
  searchSpecialist: Api_User.search,
  me: Api_User.me,
  patients: Api_Patient.list,

  patient: Api_Patient.single,
  visits: Api_Visit.list,
  calls: Api_Call.list,
};

[@bs.module "express-graphql"]
external make:
  ([@bs.uncurry] (request => graphQlConfig)) => Express.Middleware.t =
  "graphqlHTTP";

[@bs.module "graphql"] external build: string => schema = "buildSchema";
