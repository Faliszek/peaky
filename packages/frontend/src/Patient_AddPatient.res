@react.component
let make = (~visible, ~onClose, ~onCreate, ~loading) => {
  let (firstName, setFirstName) = React.useState(_ => "")
  let (lastName, setLastName) = React.useState(_ => "")
  let (phoneNumber, setPhoneNumber) = React.useState(_ => "")

  let (disease, setDisease) = React.useState(_ => "")
  let (color, setColor) = React.useState(_ => "")

  <SideNav title=`Dodawanie pacjenta` visible onClose>
    <Input.Wrap>
      <Input value=firstName onChange={v => setFirstName(_ => v)} placeholder=`Imię` />
    </Input.Wrap>
    <Input.Wrap>
      <Input value=lastName onChange={v => setLastName(_ => v)} placeholder=`Nazwisko` />
    </Input.Wrap>
    <Input.Wrap>
      <Input
        value=phoneNumber
        onChange={v => setPhoneNumber(_ => v)}
        placeholder=`Numer telefonu`
        icon={<Icons.Phone />}
      />
    </Input.Wrap>
    <Input.Wrap>
      <Input
        value=disease
        onChange={v => setDisease(_ => v)}
        placeholder=`Przypadłość`
        icon={<Icons.Thermometer />}
      />
    </Input.Wrap>
    <Color_Picker value=color onChange={v => setColor(_ => v)} />
    <div className="flex justify-center">
      <Button.CTA
        loading
        onClick={_ => onCreate(~firstName, ~lastName, ~phoneNumber, ~disease, ~color)->ignore}
        icon={<Icons.Plus className="mr-4" />}>
        <Text> `Dodaj pacjenta` </Text>
      </Button.CTA>
    </div>
  </SideNav>
}
