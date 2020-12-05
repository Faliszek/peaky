let graphqlEndpoint = "localhost:4000/graphql";

let headers = {"high": "five"};

let httpLink =
  ApolloClient.Link.HttpLink.make(
    ~uri=_ => "http://" ++ graphqlEndpoint,
    ~headers=Obj.magic(headers),
    (),
  );

// let wsLink =
//   ApolloClient.Link.WebSocketLink.(
//     make(
//       ~uri="ws://" ++ graphqlEndpoint,
//       ~options=
//         ClientOptions.make(
//           ~connectionParams=
//             ConnectionParams(Obj.magic({"headers": headers})),
//           ~reconnect=true,
//           (),
//         ),
//       (),
//     )
//   );

let terminatingLink =
  ApolloClient.Link.split(
    ~test=
      ({query}) => {
        let definition = ApolloClient.Utilities.getOperationDefinition(query);
        switch (definition) {
        | Some({kind, operation}) =>
          kind === "OperationDefinition" && operation === "subscription"
        | None => false
        };
      },
    // ~whenTrue=wsLink,
    ~whenFalse=httpLink,
  );

let instance =
  ApolloClient.(
    make(
      ~cache=Cache.InMemoryCache.make(),
      ~connectToDevTools=true,
      ~defaultOptions=
        DefaultOptions.make(
          ~mutate=
            DefaultMutateOptions.make(
              ~awaitRefetchQueries=true,
              ~errorPolicy=All,
              (),
            ),
          ~query=
            DefaultQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          ~watchQuery=
            DefaultWatchQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          (),
        ),
      ~link=httpLink,
      (),
    )
  );

[@react.component]
let make = () => {
  let token = Auth.getToken();
  let url = ReasonReactRouter.useUrl();

  Js.log(token);

  <ApolloClient.React.ApolloProvider client=instance>
    <div>
      {switch (token) {
       | None => <SignIn_View />
       | Some(_) =>
         <Layout>
           {switch (url.path) {
            | ["patients", id, "chat"] => <Patient_Chat_View id />
            | ["patients", id] => <Patient_Details_View id />
            | ["patients"] => <Patient_List_View />
            | ["visits"] => <Visits />
            | ["friends"] => <Friends />
            | [] => <Calendar />

            | _ => React.null
            }}
         </Layout>
       }}
    </div>
  </ApolloClient.React.ApolloProvider>;
};
