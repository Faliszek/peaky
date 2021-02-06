type payload = {user_id: string};
[@bs.module "jwt-decode"]
external decode: option(string) => payload = "default";

let getToken = () => Dom.Storage2.(getItem(localStorage, "token"));

let getUserId = () => {
  let {user_id} = getToken()->decode;
  user_id;
};

let signIn = (~token) => {
  switch (token) {
  | Some(token) =>
    Dom.Storage2.(setItem(localStorage, "token", token));
    ApolloClient.Bindings.Client.Link.Context.setContext(
      (~operation as _, ~prevContext as _) => {
      Js.Json.object_(Obj.magic({"Authorization": token}))
    })
    ->ignore;
    ();
  | None => ()
  };
  Router.(push(Calendar));
};

let signOut = () => {
  Dom.Storage2.(removeItem(localStorage, "token"));
  Router.(push(SignIn));
};
