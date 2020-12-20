open Patient;
let patients: array(t) = [|
  {
    id: 1,
    firstName: {j|Adam|j},
    lastName: {j|Smith|j},
    disease: {j|Depresja|j},
    condition: {j|Dobry|j},
    avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),

    phoneNumber: {j|+48 674 300 232|j},
    lastVisit: None,
  },
  {
    id: 2,
    firstName: {j|John|j},
    lastName: {j|Malković|j},
    disease: {j|Nerwica natręctw|j},
    condition: {j|Dobry|j},
    phoneNumber: {j|+48 570 300 232|j},
    avatar: None,
    lastVisit: Some({j|22.11.2020 15:30|j}),
  },
  {
    id: 3,
    firstName: {j|John|j},
    lastName: {j|Malković|j},
    disease: {j|Nerwica natręctw|j},
    condition: {j|Dobry|j},
    phoneNumber: {j|+48 570 300 232|j},
    avatar: None,
    lastVisit: Some({j|22.11.2020 15:30|j}),
  },
  {
    id: 5,
    firstName: {j|John|j},
    lastName: {j|Malković|j},
    disease: {j|Nerwica natręctw|j},
    condition: {j|Dobry|j},
    phoneNumber: {j|+48 570 300 232|j},
    avatar: None,
    lastVisit: Some({j|22.11.2020 15:30|j}),
  },
|];

[@react.component]
let make = () => {
  let (creatorVisible, setCreatorVisible) = React.useState(_ => false);
  let (firstName, setFirstName) = React.useState(_ => "");
  let (lastName, setLastName) = React.useState(_ => "");
  let (phoneNumber, setPhoneNumber) = React.useState(_ => "");

  let disease = Select.use();

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
      <div className="flex flex-wrap justify-between items-stretch">
        {patients
         ->Array.map(patient =>
             <Patient_Block patient className=" w-1/3 flex-auto mb-8 mr-12" />
           )
         ->React.array}
      </div>
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
        <Select
          value={disease.value}
          onChange={disease.setValue}
          search={disease.search}
          onSearchChange={disease.setSearch}
          visible={disease.visible}
          onVisibleChange={disease.setVisible}
          placeholder={j|Przypadłość|j}
          icon={<Icons.Thermometer />}
          options=[|{value: "1", label: {j|Nadciśnienie tętnicze|j}}|]
        />
      </Input.Wrap>
    </SideNav>
  </Page>;
};
