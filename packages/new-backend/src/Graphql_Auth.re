open Belt.Result;

let signIn =
    ({email, password}: Auth.payload, context: Graphql_Context.t, _, _) => {
  context.auth
  ->Auth.signInWithEmailAndPassword(~email, ~password)
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.Js.map(res => {
      switch (res) {
      | Ok(res) => Some(res.user.refreshToken)
      | Error(_) => None
      }
    });
};
