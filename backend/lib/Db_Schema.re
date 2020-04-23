module User = {
  let table = "p_users";

  type t = {
    id: string,
    email: string,
  };

  let create = (~email) => ();
};