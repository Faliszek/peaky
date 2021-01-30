module Colors = {
  let colors = [|
    "#F87171",
    "#FB923C",
    "#FBBF24",
    "#FACC15",
    "#A3E635",
    "#4ADE80",
    "#34D399",
    "#2DD4BF",
    "#22D3EE",
    "#38BDF8",
    "#60A5FA",
    "#818CF8",
    "#A78BFA",
    "#C084FC",
    "#F5D0FE",
  |];

  [@react.component]
  let make = (~value, ~onChange) => {
    <div className="mb-12 mt-8 flex flex-wrap gap-4">
      {{
         colors->Array.map(c => {
           let active = value == c ? "ring-4 ring-green-400" : "";
           <div
             key=c
             onClick={_ => onChange(c)}
             className=Cn.(
               "w-10 h-10 rounded-md shadow-md border border-gray-100 cursor-pointer"
               + active
             )
             style={ReactDOM.Style.make(~backgroundColor=c, ())}
           />;
         });
       }
       ->React.array}
    </div>;
  };
};

[@react.component]
let make = (~visible, ~onClose, ~onCreate, ~loading) => {
  let (firstName, setFirstName) = React.useState(_ => "");
  let (lastName, setLastName) = React.useState(_ => "");
  let (phoneNumber, setPhoneNumber) = React.useState(_ => "");

  let (disease, setDisease) = React.useState(_ => "");
  let (color, setColor) = React.useState(_ => "");

  <SideNav title={j|Dodawanie pacjenta|j} visible onClose>
    <Input.Wrap>
      <Input
        value=firstName
        onChange={v => setFirstName(_ => v)}
        placeholder={j|Imię|j}
      />
    </Input.Wrap>
    <Input.Wrap>
      <Input
        value=lastName
        onChange={v => setLastName(_ => v)}
        placeholder={j|Nazwisko|j}
      />
    </Input.Wrap>
    <Input.Wrap>
      <Input
        value=phoneNumber
        onChange={v => setPhoneNumber(_ => v)}
        placeholder={j|Numer telefonu|j}
        icon={<Icons.Phone />}
      />
    </Input.Wrap>
    <Input.Wrap>
      <Input
        value=disease
        onChange={v => setDisease(_ => v)}
        placeholder={j|Przypadłość|j}
        icon={<Icons.Thermometer />}
      />
    </Input.Wrap>
    <Colors value=color onChange={v => setColor(_ => v)} />
    <div className="flex justify-center">
      <Button.CTA
        loading
        onClick={_ =>
          onCreate(~firstName, ~lastName, ~phoneNumber, ~disease, ~color)
          ->ignore
        }
        icon={<Icons.Plus className="mr-4" />}>
        <Text> {j|Dodaj pacjenta|j} </Text>
      </Button.CTA>
    </div>
  </SideNav>;
};
