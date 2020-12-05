let getToken = () => Dom.Storage2.(getItem(localStorage, "token"));

let signIn = (~token) => {
  switch (token) {
  | Some(token) => Dom.Storage2.(setItem(localStorage, "token", token))
  | None => ()
  };
  Router.(push(Calendar));
};

let signOut = () => {
  Dom.Storage2.(removeItem(localStorage, "token"));
  Router.(push(SignIn));
};
