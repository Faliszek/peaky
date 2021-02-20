type payload = {user_id: string}
@module("jwt-decode")
external decode: option<string> => payload = "default"

let getToken = () => {
  open Dom.Storage2
  getItem(localStorage, "token")
}

let getUserId = () => {
  let {user_id} = getToken()->decode
  user_id
}

let signIn = (~token) => {
  switch token {
  | Some(token) =>
    {
      open Dom.Storage2
      setItem(localStorage, "token", token)
    }
    ApolloClient.Bindings.Client.Link.Context.setContext((~operation as _, ~prevContext as _) =>
      Js.Json.object_(Obj.magic({"Authorization": token}))
    )->ignore
    ()
  | None => ()
  }
  open Router
  push(Calendar)
}

let signOut = () => {
  {
    open Dom.Storage2
    removeItem(localStorage, "token")
  }
  open Router
  push(SignIn)
}
