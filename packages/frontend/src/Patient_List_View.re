open Patient;

module Colors = {
  let colors = [|
    ("50", "#FEF2F2"),
    ("100", "#FEE2E2"),
    ("200", "#FECACA"),
    ("300", "#FCA5A5"),
    ("400", "#F87171"),
    ("500", "#EF4444"),
    ("600", "#DC2626"),
    ("700", "#B91C1C"),
    ("800", "#991B1B"),
    ("900", "#7F1D1D"),
    ("50", "#FFF7ED"),
    ("100", "#FFEDD5"),
    ("200", "#FED7AA"),
    ("300", "#FDBA74"),
    ("400", "#FB923C"),
    ("500", "#F97316"),
    ("600", "#EA580C"),
    ("700", "#C2410C"),
    ("800", "#9A3412"),
    ("900", "#7C2D12"),
    ("50", "#FFFBEB"),
    ("100", "#FEF3C7"),
    ("200", "#FDE68A"),
    ("300", "#FCD34D"),
    ("400", "#FBBF24"),
    ("500", "#F59E0B"),
    ("600", "#D97706"),
    ("700", "#B45309"),
    ("800", "#92400E"),
    ("900", "#78350F"),
    ("50", "#FEFCE8"),
    ("100", "#FEF9C3"),
    ("200", "#FEF08A"),
    ("300", "#FDE047"),
    ("400", "#FACC15"),
    ("500", "#EAB308"),
    ("600", "#CA8A04"),
    ("700", "#A16207"),
    ("800", "#854D0E"),
    ("900", "#713F12"),
    ("50", "#F7FEE7"),
    ("100", "#ECFCCB"),
    ("200", "#D9F99D"),
    ("300", "#BEF264"),
    ("400", "#A3E635"),
    ("500", "#84CC16"),
    ("600", "#65A30D"),
    ("700", "#4D7C0F"),
    ("800", "#3F6212"),
    ("900", "#365314"),
    ("50", "#F0FDF4"),
    ("100", "#DCFCE7"),
    ("200", "#BBF7D0"),
    ("300", "#86EFAC"),
    ("400", "#4ADE80"),
    ("500", "#22C55E"),
    ("600", "#16A34A"),
    ("700", "#15803D"),
    ("800", "#166534"),
    ("900", "#14532D"),
    ("50", "#ECFDF5"),
    ("100", "#D1FAE5"),
    ("200", "#A7F3D0"),
    ("300", "#6EE7B7"),
    ("400", "#34D399"),
    ("500", "#10B981"),
    ("600", "#059669"),
    ("700", "#047857"),
    ("800", "#065F46"),
    ("900", "#064E3B"),
    ("50", "#F0FDFA"),
    ("100", "#CCFBF1"),
    ("200", "#99F6E4"),
    ("300", "#5EEAD4"),
    ("400", "#2DD4BF"),
    ("500", "#14B8A6"),
    ("600", "#0D9488"),
    ("700", "#0F766E"),
    ("800", "#115E59"),
    ("900", "#134E4A"),
    ("50", "#ECFEFF"),
    ("100", "#CFFAFE"),
    ("200", "#A5F3FC"),
    ("300", "#67E8F9"),
    ("400", "#22D3EE"),
    ("500", "#06B6D4"),
    ("600", "#0891B2"),
    ("700", "#0E7490"),
    ("800", "#155E75"),
    ("900", "#164E63"),
    ("50", "#F0F9FF"),
    ("100", "#E0F2FE"),
    ("200", "#BAE6FD"),
    ("300", "#7DD3FC"),
    ("400", "#38BDF8"),
    ("500", "#0EA5E9"),
    ("600", "#0284C7"),
    ("700", "#0369A1"),
    ("800", "#075985"),
    ("900", "#0C4A6E"),
    ("50", "#EFF6FF"),
    ("100", "#DBEAFE"),
    ("200", "#BFDBFE"),
    ("300", "#93C5FD"),
    ("400", "#60A5FA"),
    ("500", "#3B82F6"),
    ("600", "#2563EB"),
    ("700", "#1D4ED8"),
    ("800", "#1E40AF"),
    ("900", "#1E3A8A"),
    ("50", "#EEF2FF"),
    ("100", "#E0E7FF"),
    ("200", "#C7D2FE"),
    ("300", "#A5B4FC"),
    ("400", "#818CF8"),
    ("500", "#6366F1"),
    ("600", "#4F46E5"),
    ("700", "#4338CA"),
    ("800", "#3730A3"),
    ("900", "#312E81"),
    ("50", "#F5F3FF"),
    ("100", "#EDE9FE"),
    ("200", "#DDD6FE"),
    ("300", "#C4B5FD"),
    ("400", "#A78BFA"),
    ("500", "#8B5CF6"),
    ("600", "#7C3AED"),
    ("700", "#6D28D9"),
    ("800", "#5B21B6"),
    ("900", "#4C1D95"),
    ("50", "#FAF5FF"),
    ("100", "#F3E8FF"),
    ("200", "#E9D5FF"),
    ("300", "#D8B4FE"),
    ("400", "#C084FC"),
    ("500", "#A855F7"),
    ("600", "#9333EA"),
    ("700", "#7E22CE"),
    ("800", "#6B21A8"),
    ("900", "#581C87"),
    ("50", "#FDF4FF"),
    ("100", "#FAE8FF"),
    ("200", "#F5D0FE"),
    ("300", "#F0ABFC"),
    ("400", "#E879F9"),
    ("500", "#D946EF"),
    ("600", "#C026D3"),
    ("700", "#A21CAF"),
    ("800", "#86198F"),
    ("900", "#701A75"),
    ("50", "#FDF2F8"),
    ("100", "#FCE7F3"),
    ("200", "#FBCFE8"),
    ("300", "#F9A8D4"),
    ("400", "#F472B6"),
    ("500", "#EC4899"),
    ("600", "#DB2777"),
    ("700", "#BE185D"),
    ("800", "#9D174D"),
    ("900", "#831843"),
    ("50", "#FFF1F2"),
    ("100", "#FFE4E6"),
    ("200", "#FECDD3"),
    ("300", "#FDA4AF"),
    ("400", "#FB7185"),
    ("500", "#F43F5E"),
    ("600", "#E11D48"),
    ("700", "#BE123C"),
    ("800", "#9F1239"),
    ("900", "#881337"),
  |];

  [@react.component]
  let make = (~value, ~onChange) => {
    <div className="mb-6 flex flex-wrap gap-2">
      {{
         colors->Array.map(c => {
           let active = value == c ? "ring-4 ring-green-400" : "";
           <div
             key=c
             onClick={_ => onChange(c)}
             className=Cn.(
               "w-8 h-8 rounded-md shadow-md border border-gray-100 cursor-pointer"
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
let make = () => {
  let (creatorVisible, setCreatorVisible) = React.useState(_ => false);
  let (firstName, setFirstName) = React.useState(_ => "");
  let (lastName, setLastName) = React.useState(_ => "");
  let (phoneNumber, setPhoneNumber) = React.useState(_ => "");

  let (disease, setDisease) = React.useState(_ => "");
  let (color, setColor) = React.useState(_ => "");

  let queryUsers = Patient_List_Query.Query.use();

  <Page
    title="Pacjenci"
    actions={
      <Button.CTA
        onClick={_ => setCreatorVisible(_ => true)}
        icon={<Icons.Plus className="mr-4" />}>
        <Text> {j|Dodaj pacjenta|j} </Text>
      </Button.CTA>
    }>
    <div>
      <div className="flex flex-wrap justify-between items-stretch" />
      {switch (queryUsers) {
       | {loading: true} => <Spinner />
       | {data: Some(data)} =>
         data.patients
         ->Array.map(patient =>
             <Patient_Block
               key={patient.id}
               patient
               className=" w-1/3 flex-auto mb-8 mr-12"
             />
           )
         ->React.array
       | _ => React.null
       }}
    </div>
    <SideNav
      title={j|Dodawanie pacjenta|j}
      visible=creatorVisible
      onClose={_ => setCreatorVisible(_ => false)}>
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
    </SideNav>
  </Page>;
};
