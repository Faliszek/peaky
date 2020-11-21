type error = ApolloClient__Errors_ApolloError.t;
type response('a) = ApolloClient__React_Types.FetchResult.t__ok('a);

let onFinish = (req, ~onOk: 'a => unit, ~onError) => {
  req
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.Js.get(res => {
      let generalError = {j|Coś poszło nie tak|j};
      let networkError = {j|Nie mogliśmy nawiązać połączenia z serwerem, sprawdzamy co się dzieje|j};

      switch (res) {
      | Ok(res) =>
        switch (res) {
        | Ok(res: response('a)) =>
          onOk(res.data);

          res.error
          ->Option.map(err =>
              Error.handleError(~feedback="Domain error (?)", err)
            )
          ->ignore;

        | Error(error: error) =>
          switch (error.networkError, error.graphQLErrors) {
          | (Some(_), _) =>
            Error.handleError(~feedback="Network error", networkError)
          | (None, errors) =>
            Error.handleError(~feedback="Probably domain error", errors);
            onError(errors);
          }
        }
      | Error(error) => Error.handleError(~feedback=generalError, error)
      };
    });
};
