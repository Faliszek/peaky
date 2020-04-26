let table = "p_users";

module Domain = {
  type t = {
    id: string,
    email: string,
    password: string,
  };
};

module Api = {
  type t = {
    id: string,
    email: string,
  };
};

let toApi: 't => option(Api.t) =
  user => {
    open Api;
    let user =
      switch (user) {
      | [id, email, _] =>
        Some(Pgx_value.(to_string(id), to_string(email)))
      | _ => None
      };

    user
    |> Option.bind(_, ((id, email)) =>
         switch (id, email) {
         | (Some(id), Some(email)) => Some({id, email})
         | _ => None
         }
       );
  };