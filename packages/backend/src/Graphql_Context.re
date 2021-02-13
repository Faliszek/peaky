type t = {
  auth: Firebase.Auth.t,
  db: Firebase.Database.t,
  token: option(string),
};
