open User.DTO;

let fromRow = u => {
  switch (u) {
  | [id, email, password, archived, createdAt, updatedAt] =>
    Some(
      Pgx_value.(
        to_string(id),
        to_string(email),
        to_string(password),
        to_bool(archived),
        to_string(createdAt),
        to_string(updatedAt),
      ),
    )
  | _ => None
  };
};

let toDTO = ((id, email, password, archived, createdAt, updatedAt)) =>
  switch (id, email, password, archived, createdAt, updatedAt) {
  | (
      Some(id),
      Some(email),
      Some(password),
      Some(archived),
      Some(createdAt),
      Some(updatedAt),
    ) =>
    Some({id, email, password, archived, createdAt, updatedAt})
  | _ => None
  };

let getAll = () => {
  Users_Inf.getAll()
  |> Lwt.map(users =>
       users
       |> List.map(fromRow)
       |> F.List.collect
       |> List.map(toDTO)
       |> F.List.collect
     );
};

let getOne = (~id) => {
  let user = Users_Inf.getOne(~id);

  user |> Lwt.map(u => u |> Option.bind(_, fromRow) |> Option.bind(_, toDTO));
};

let getByEmail = (~email) => {
  let user = Users_Inf.getByEmail(~email);

  user |> Lwt.map(u => u |> Option.bind(_, fromRow) |> Option.bind(_, toDTO));
};

let create = (~email, ~password) => {
  Users_Inf.create(~email, ~password);
};

let setArchived = (~id, ~value) => {
  Users_Inf.setArchived(~id, ~value)
  |> Lwt.map(u => u |> Option.bind(_, fromRow) |> Option.bind(_, toDTO));
};
