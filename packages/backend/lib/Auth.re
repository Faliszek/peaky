type error =
  | WrongCredentials;

type tokenPayloadDTO = {token: string};

type loginResponse = {
  result: option(tokenPayloadDTO),
  errors: option(list(error)),
};
