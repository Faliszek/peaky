open Graphql_lwt;
open Jose;

let expirationDateInMs = (~days) => 1000.0 *. 60.0 *. 60.0 *. 24.0 *. days;

let createSignedToken = (~id) => {
  let rsa = Mirage_crypto_pk.Rsa.generate(~bits=2048, ());
  let crypto =
    Mirage_crypto_pk.Rsa.priv(
      ~e=rsa.e,
      ~d=rsa.d,
      ~n=rsa.n,
      ~p=rsa.p,
      ~q=rsa.q,
      ~dp=rsa.dp,
      ~dq=rsa.dq,
      ~q'=rsa.q',
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
