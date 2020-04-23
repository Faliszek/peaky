let table = "p_users";

type t = {
  id: string,
  email: string,
};

let create = (~email) => ();

module Db = {
  type t = {
    id: string,
    email: string,
    password: string,
  };

  let toApi = user => {
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
};