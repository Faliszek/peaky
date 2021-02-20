let graphqlEndpoint = "localhost:4000/graphql"

let subscriptionEndpoint = "localhost:4001/subscriptions"

let headers = {"high": "five"}

let httpLink = ApolloClient.Link.HttpLink.make(
  ~uri=_ => "http://" ++ graphqlEndpoint,
  ~headers=Obj.magic(headers),
  (),
)

let wsLink = {
  open ApolloClient.Link.WebSocketLink
  make(
    ~uri="ws://" ++ subscriptionEndpoint,
    ~options=ClientOptions.make(
      ~connectionParams=ConnectionParams(Obj.magic({"headers": headers})),
      ~reconnect=true,
      (),
    ),
    (),
  )
}

let authPayload = token =>
  {
    "headers": {
      "Authorization": token,
    },
  }

let authLink = ApolloClient.Bindings.Client.Link.Context.setContext((
  ~operation as _,
  ~prevContext as _,
) => {
  let token = Auth.getToken()

  switch token {
  | Some(token) => authPayload(token)->Obj.magic
  | None => Js.Obj.empty()->Obj.magic
  }
})

let terminatingLink = ApolloClient.Link.split(~test=({query}) => {
  let definition = ApolloClient.Utilities.getOperationDefinition(query)
  switch definition {
  | Some({kind, operation}) => kind === "OperationDefinition" && operation === "subscription"
  | None => false
  }
}, ~whenTrue=wsLink, ~whenFalse=httpLink)

let instance = {
  open ApolloClient
  make(
    ~cache=Cache.InMemoryCache.make(),
    ~connectToDevTools=true,
    ~defaultOptions=DefaultOptions.make(
      ~mutate=DefaultMutateOptions.make(~awaitRefetchQueries=true, ~errorPolicy=All, ()),
      ~query=DefaultQueryOptions.make(~fetchPolicy=NetworkOnly, ~errorPolicy=All, ()),
      ~watchQuery=DefaultWatchQueryOptions.make(~fetchPolicy=NetworkOnly, ~errorPolicy=All, ()),
      (),
    ),
    ~link=ApolloClient.Link.concat(authLink, httpLink),
    (),
  )
}
