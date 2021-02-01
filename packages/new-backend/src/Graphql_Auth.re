open Firebase;

// type t;

// module User = {
//   type t = {refreshToken: string};
// };

// type signInResponse = {user: User.t};
// [@bs.send]
// external signInWithEmailAndPassword:
//   (t, ~email: string, ~password: string) => Js.Promise.t(signInResponse) =
//   "signInWithEmailAndPassword";

// [@bs.module "firebase"] external make: unit => t = "auth";

type payload = {
  email: string,
  password: string,
};

let signIn = ({email, password}: payload, context: Graphql_Context.t) => {
  context.auth
  ->Auth.signInWithEmailAndPassword(~email, ~password)
  ->Promise.Js.flatMap(res => {res.user->Firebase.Auth.User.getIdToken})
  ->Promise.Js.map(Js.Nullable.toOption);
};

let createUser = (~db: Firebase.Database.t, ~uid: string, ~email: string) => {
  db
  ->Firebase.Database.ref(~path="/users/" ++ uid, ())
  ->Firebase.Database.Reference.set(~value={"email": email});
};

let signUp = ({email, password}: payload, context: Graphql_Context.t) => {
  context.auth
  ->Auth.createUserWithEmailAndPassword(~email, ~password)
  ->Promise.Js.toResult
  ->Promise.Js.map(res => {
      switch (res) {
      | Ok(res) =>
        createUser(
          ~db=context.db,
          ~uid=res.user.uid,
          ~email=res.user.email,
          (),
        )
        ->ignore;
        Some(res.user);
      | Error(_) => None
      }
    })
  ->Promise.Js.relax;
};
