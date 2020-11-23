type t;

module User = {
  type t = {refreshToken: string};
};

type signInResponse = {user: User.t};
[@bs.send]
external signInWithEmailAndPassword:
  (t, ~email: string, ~password: string) => Js.Promise.t(signInResponse) =
  "signInWithEmailAndPassword";

[@bs.module "firebase"] external make: unit => t = "auth";

type payload = {
  email: string,
  password: string,
};
