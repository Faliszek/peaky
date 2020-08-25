open Graphql_lwt;
open Jose;

type authError =
  | WrongCredentials;

type tokenPayloadDTO = {token: string};

type loginResponse = {
  result: option(tokenPayloadDTO),
  errors: option(list(authError)),
};

let expirationDateInMs = (~days) => 1000.0 *. 60.0 *. 60.0 *. 24.0 *. days;

let createSignedToken = (~id) => {
  //   let expirationDate = Unix.time() +. expirationDateInMs(~days=2.0);
  //   let payload = [("sub", id), ("exp", expirationDate |> string_of_float)];

  let key = Mirage_crypto_pk.Rsa.generate(~bits=2048, ());
  let crypto =
    Mirage_crypto_pk.Rsa.priv(
      ~e=key.e,
      ~d=key.d,
      ~n=key.n,
      ~p=key.p,
      ~q=key.q,
      ~dp=key.dp,
      ~dq=key.dq,
      ~q'=key.q',
    );

  let expirationDate = expirationDateInMs(~days=2.0);

  let payload =
    `Assoc([
      ("sub", `String(id)),
      ("exp", `String(expirationDate |> string_of_float)),
    ]);
  switch (crypto) {
  | Ok(result) =>
    let rsa = Jose.Jwk.make_priv_rsa(result);
    switch (rsa) {
    | p =>
      let header = Header.make_header(p);
      let token = Jwt.sign(~header, ~payload, p);
      switch (token) {
      | Ok(token) => Some(token)
      | Error(msg) => None
      };
    };

  | Error(msg) => None
  };
};

/*TODO: this function probably§ should return some record
  with informaiton if email exist, option(token) etc. for now option(token) is cool */

let authenticateUser = (~email, ~password) => {
  Users_DTO.getByEmail(~email)
  |> Lwt.map(user => {
       switch (user) {
       | Some(user: User.DTO.t)
           when
             Bcrypt.verify(password, user.password |> Bcrypt.hash_of_string) =>
         print_endline("Auth!!!");
         createSignedToken(~id=user.id);

       | _ =>
         print_endline("Not auth");
         None;
       }
     });
};

let authError: Graphql_lwt.Schema.typ(Hmap.t, option(authError)) =
  Schema.(
    enum(
      "AuthenticateResponseError",
      ~values=[
        enum_value(
          "INVALID_CREDENTIALS",
          ~value=WrongCredentials,
          ~doc="Invalid email error",
        ),
      ],
    )
  );

let result =
  Schema.(
    obj("LoginResult", ~fields=_ =>
      [
        Schema.(
          io_field(
            "token", ~typ=non_null(string), ~args=Arg.[], ~resolve=(ctx, s) =>
            Lwt_result.return(s.token)
          )
        ),
      ]
    )
  );

let resultField =
  Schema.(
    io_field("result", ~typ=result, ~args=Arg.[], ~resolve=(ctx, r) =>
      Lwt_result.return(Some({token: r.token}))
    )
  );

let loginResponse: Graphql_lwt.Schema.typ(Hmap.t, option(loginResponse)) =
  Schema.(
    obj("LoginResponse", ~doc="Login auth result", ~fields=_ =>
      [
        io_field("result", ~typ=result, ~args=Arg.[], ~resolve=(ctx, s) =>
          Lwt_result.return(s.result)
        ),
        io_field(
          "errors",
          ~typ=list(non_null(authError)),
          ~args=Arg.[],
          ~resolve=(ctx, s) => {
          s.errors |> Lwt_result.return
        }),
      ]
    )
  );

let loginMutation: Graphql_lwt.Schema.field(Hmap.t, unit) = {
  Schema.(
    io_field(
      "signIn",
      ~typ=non_null(loginResponse),
      ~args=
        Arg.[
          arg("email", ~typ=non_null(string)),
          arg("password", ~typ=non_null(string)),
        ],
      ~resolve=(ctx, _, email, password) => {
        let loginResponse =
          authenticateUser(~email, ~password)
          |> Lwt.map(token =>
               switch (token) {
               | Some(token) => {
                   errors: None,
                   result: Some({token: Jwt.to_string(token)}),
                 }
               | None => {errors: Some([WrongCredentials]), result: None}
               }
             );

        Lwt_result.ok(loginResponse);
      },
    )
  );
};

let mutations = [loginMutation];
