open Patient
let patient = {
  id: 1,
  firstName: `Adam`,
  lastName: `Smith`,
  disease: `Depresja`,
  condition: `Dobry`,
  avatar: Some(`https://www.thispersondoesnotexist.com/image`),
  phoneNumber: `+48 674 300 232`,
  lastVisit: None,
}

type message = {
  id: int,
  text: string,
  author: string,
}
let messages: array<message> = []

module Status = {
  @react.component
  let make = (~status, ~className=?) => {
    let bg = switch status {
    | #online => "bg-green-300"
    | #offline => "bg-red-300"
    }

    <div
      className={
        open Cn
        "w-4 h-4 rounded-full" + bg + mapSome(className, x => x)
      }
    />
  }
}

@send external focus: Dom.element => unit = "focus"

module Message = {
  @react.component
  let make = (~text) => <div> <Text> text </Text> </div>
}
@react.component
let make = (~_id) => {
  let {lastName, firstName} = patient

  let name = firstName ++ (" " ++ lastName)
  let textarea = React.useRef(Js.Nullable.null)

  let (message, setMessage) = React.useState(_ => "")
  React.useEffect1(() => {
    switch textarea.current->Js.Nullable.toOption {
    | Some(textarea) => focus(textarea)
    | _ => ()
    }
    None
  }, [textarea])

  let loading = false

  <div className="flex flex-col h-screen w-full relative">
    <div
      className="w-full shadow-lg px-4 flex flex-row items-center absolute top-0 h-28 justify-between">
      <div className="flex justify-center items-center">
        <Avatar lastName firstName />
        <h1 className="ml-8 text-3xl"> <Text> name </Text> </h1>
        <Status status=#online className="ml-4" />
      </div>
      <div>
        <Button.CTA icon={<Icons.Plus className="mr-4" />}>
          <Text> `Dodaj wizytę` </Text>
        </Button.CTA>
      </div>
    </div>
    <div className="w-full h-full flex flex-col pt-28 pb-36">
      <div className="bg-gray-50 flex-1  overflow-y-auto">
        {switch (loading, messages) {
        | (false, []) =>
          <div className="text-gray-300 h-full flex items-center flex-col justify-center">
            <Icons.Inbox size="64" />
            <span className="mt-4 text-4xl"> <Text> `Brak wiadomości` </Text> </span>
          </div>
        | (false, messages) => messages->Array.map(m => <Message text=m.text />)->React.array
        | (true, _) => <Icons.Spinner />
        }}
      </div>
      <div
        className="p-4 absolute bottom-0 h-36 border-top border flex items-center justify-center w-full">
        <Input.Textarea
          value=message
          onChange={v => setMessage(_ => v)}
          ref_={ReactDOM.Ref.domRef(textarea)}
          placeholder=`Napisz wiadomość`
        />
        <Button.SmallRound icon={<Icons.Send />} onClick={_ => ()} />
      </div>
    </div>
  </div>
}
