module SignIn = [%graphql
  {|
  mutation SignIn($email: String!, $password: String!) {
    signIn(email: $email, password:$password)
  }
|}
];

module LoginForm = [%form
  type input = {
    email: string,
    password: string,
  };
  type output = input;
  let validators = {email: None, password: None}
];

let initialState: LoginForm.input = {email: "", password: ""};

[@react.component]
let make = () => {
  let (signIn, _) = SignIn.use();

  let form =
    LoginForm.useForm(
      ~initialInput=initialState,
      ~onSubmit=({email, password}, actions) => {
        // Js.log2(output, cb);
        signIn({email, password}) |> ignore;
        actions.notifyOnFailure();
      },
    );

  let {email, password}: LoginForm.input = form.input;

  <div className="w-full min-h-screen bg-blue-300">
    <form
      onSubmit={e => {
        e->ReactEvent.Form.preventDefault;
        form.submit();
      }}>
      <div className="py-32 w-1/3 m-auto">
        <h1 className="text-4xl mb-8 text-center text-gray-100">
          <Text> {j|Autentykacja|j} </Text>
        </h1>
        <div
          className="shadow-xl rounded-xl px-8 py-16 border border-gray-100 bg-white  flex flex-col justify-center">
          <div className="pb-8">
            <Input
              placeholder={j|E-mail|j}
              value=email
              onChange={email =>
                form.updateEmail(
                  (input, value) => {...input, email: value},
                  email,
                )
              }
              className="border border-gray-300 rounded-lg px-4 py-2 text-lg"
            />
          </div>
          <div className="pb-8">
            <Input
              placeholder={j|Hasło|j}
              value=password
              onChange={password =>
                form.updatePassword(
                  (input, value) => {...input, password: value},
                  password,
                )
              }
              className="border border-gray-300 rounded-lg px-4 py-2 text-lg"
              _type="password"
            />
          </div>
          <div className="flex justify-center">
            <Button
              _type=`primary
              shape=`round
              htmlType="submit"
              className="text-lg px-8 h-12 font-medium shadow-lg flex items-center justify-center"
              loading={form.submitting}>
              <span className="pl-1"> <Text> {j|Zaloguj się|j} </Text> </span>
            </Button>
          </div>
          <div className="text-md text-gray-600 text-center mt-8">
            <Text> {j|Zapomniałeś hasła?|j} </Text>
          </div>
        </div>
      </div>
    </form>
  </div>;
};
