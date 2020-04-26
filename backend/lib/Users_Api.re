let toApi = (u: User.DTO.t) => User.Api.{id: u.id, email: u.email};

let getOne = (~id) => {
  let user = Users_DTO.getOne(~id);

  user |> Lwt.map(u => u |> Option.map(toApi));
};

let getAll = () => {
  let users = Users_DTO.getAll();

  users |> Lwt.map(users => users |> List.map(toApi));
};

let create = (~email, ~password) => {
  Users_Inf.create(~email, ~password);
};