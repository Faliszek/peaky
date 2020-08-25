let table = "p_users";

module DTO = {
  type t = {
    id: string,
    email: string,
    password: string,
    archived: bool,
    createdAt: string,
    updatedAt: string,
  };
};

module Domain = {
  type t = {
    id: string,
    email: string,
    password: string,
    archived: bool,
  };
};

module Api = {
  type t = {
    id: string,
    email: string,
    archived: bool,
  };
};