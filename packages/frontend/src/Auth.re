let signIn = (~token) =>
  switch (token) {
  | Some(token) => Dom.Storage2.(setItem(localStorage, "token", token))
  | None => ()
  };

let signOut = () => Dom.Storage2.(removeItem(localStorage, "token"));
