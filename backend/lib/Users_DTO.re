open User.DTO;

let fromRow = u => {
  switch (u) {
  | [id, email, password, createdAt, updatedAt] =>
    Some(
      Pgx_value.(
        to_string(id),
        to_string(email),
        to_string(password),
        to_string(createdAt),
        to_string(updatedAt),
      ),
    )
  | _ => None
  };
};

let toDTO = ((id, email, password, createdAt, updatedAt)) =>
  switch (id, email, password, createdAt, updatedAt) {
  | (
      Some(id),
      Some(email),
      Some(password),
      Some(createdAt),
      Some(updatedAt),
    ) =>
    Some({id, email, password, createdAt, updatedAt})
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