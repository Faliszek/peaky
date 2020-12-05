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
  let (signIn, result) = SignIn.use();

  let form =
    LoginForm.useForm(
      ~initialInput=initialState,
      ~onSubmit=({email, password}, actions) => {
        signIn({email, password})
        ->Request.onFinish(
            ~onOk=
              ({signIn}) => {
                Auth.signIn(~token=signIn);
                Router.(push(Calendar));
              },
            ~onError=_ => (),
          );

        actions.notifyOnFailure();
      },
    );

  let {email, password}: LoginForm.input = form.input;

  <div className="relative w-full min-h-screen flex">
    <div
      className="bg-white absolute  w-full h-full rounded-bl-full flex justify-center items-center shadow-xl overflow-hidden z-10 opacity-90 "
      style={ReactDOMStyle.make(~top="-20%", ~right="-20%", ())}>
      <Graphic_Login />
    </div>
    <div
      className="bg-green-50 absolute bottom-0 left-0 h-screen flex items-center w-full">
      <div className="fixed flex flex-col w-1/4 bottom-0 left-0 ml-24 mb-24">
        <h1 className="text-4xl text-center mb-4 text-green-400 ">
          <Text> {j|Autentykacja|j} </Text>
        </h1>
        <form
          onSubmit={e => {
            e->ReactEvent.Form.preventDefault;
            form.submit();
          }}>
          <div className="">
            <div
              className="rounded-xl px-8 py-16 border border-gray-100 bg-white  flex flex-col justify-center shadow-lg">
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
                <Button.CTA htmlType="submit" loading={result.loading}>
                  <span className="pl-1">
                    <Text> {j|Zaloguj się|j} </Text>
                  </span>
                </Button.CTA>
              </div>
              <div className="text-md text-gray-600 text-center mt-8">
                <Text> {j|Zapomniałeś hasła?|j} </Text>
              </div>
            </div>
          </div>
        </form>
      </div>
    </div>
  </div>;
};
