// module Hello = [%graphql {|
//   query Hello {
//     hello
//   }
// |}];

[@react.component]
let make = () => {
  let (email, setEmail) = React.useState(() => "");
  let (password, setPassword) = React.useState(() => "");
  <div className="w-full min-h-screen bg-blue-300">
    <div className="py-32 w-1/3 m-auto">
      <h1 className="text-4xl mb-8 text-center text-gray-100">
        <Text> {j|Zaloguj się|j} </Text>
      </h1>
      <div
        className="shadow-xl rounded-xl px-8 py-16 border border-gray-100 bg-white  flex flex-col justify-center">
        <div className="pb-8">
          <Input
            placeholder={j|E-mail|j}
            value=email
            onChange={e => setEmail(_ => e->ReactEvent.Form.target##value)}
            autocomplete="off"
            className="border border-gray-300 rounded-lg px-4 py-2 text-lg"
          />
        </div>
        <div className="pb-8">
          <Input
            placeholder={j|Hasło|j}
            value=password
            onChange={e => setPassword(_ => e->ReactEvent.Form.target##value)}
            autocomplete="off"
            className="border border-gray-300 rounded-lg px-4 py-2 text-lg"
            _type="password"
          />
        </div>
        <div className="flex justify-center">
          <Button
            _type=`primary
            shape=`round
            className="text-lg px-8 h-12 font-medium shadow-lg ">
            <Text> {j|Zaloguj się|j} </Text>
          </Button>
        </div>
        <div className="text-md text-gray-600 text-center mt-8">
          <Text> {j|Zapomniałeś hasła?|j} </Text>
        </div>
      </div>
    </div>
  </div>;
};
