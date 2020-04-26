let table = "p_users";

module DTO = {
  type t = {
    id: string,
    email: string,
    password: string,
    createdAt: string,
    updatedAt: string,
  };
};

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