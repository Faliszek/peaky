let toApi = (u: User.DTO.t) =>
  User.Api.{id: u.id, email: u.email, archived: u.archived};

let getOne = (~id) => {
  let user = Users_DTO.getOne(~id);

  user |> Lwt.map(Option.map(toApi));
};

let getAll = () => {
  let users = Users_DTO.getAll();

  users |> Lwt.map(users => users |> List.map(toApi));
};

let create = (~email, ~password) => {
  Users_DTO.create(~email, ~password, ());
};

let archive = (~id) => {
  Users_DTO.setArchived(~id, ~value=true) |> Lwt.map(Option.map(toApi));
};

let restore = (~id) => {
  Users_DTO.setArchived(~id, ~value=false) |> Lwt.map(Option.map(toApi));
};
