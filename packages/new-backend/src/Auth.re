type payload = {
  email: string,
  password: string,
};

let signIn = ({email, password}) => {
  Js.log2(email, password);
  "fake-token";
};
