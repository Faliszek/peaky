open Patient;
// let patients: array(t) = [|
// //   // {
// //   //   id: 1,
// //   //   firstName: {j|Adam|j},
// //   //   lastName: {j|Smith|j},
// //   //   disease: {j|Depresja|j},
// //   //   condition: {j|Dobry|j},
// //   //   avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),
// //   //   phoneNumber: {j|+48 674 300 232|j},
// //   //   lastVisit: None,
// //   // },
// //   // {
// //   //   id: 2,
// //   //   firstName: {j|Seyyid|j},
// //   //   lastName: {j|Llew|j},
// //   //   disease: {j|Zaburzenia snu|j},
// //   //   condition: {j|Dobry|j},
// //   //   phoneNumber: {j|+48 570 822 212|j},
// //   //   avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),
// //   //   lastVisit: Some({j|22.11.2020 15:30|j}),
// //   // },
// //   // {
// //   //   id: 3,
// //   //   firstName: {j|Dunja|j},
// //   //   lastName: {j|Tonya|j},
// //   //   disease: {j|Alkoholizm|j},
// //   //   condition: {j|Dobry|j},
// //   //   phoneNumber: {j|+48 633 193 733|j},
// //   //   avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),
// //   //   lastVisit: Some({j|22.11.2020 15:30|j}),
// //   // },
// //   // {
// //   //   id: 5,
// //   //   firstName: {j|Niam|j},
// //   //   lastName: {j|Tapani|j},
// //   //   disease: {j|Zespół lęku napadowego|j},
// //   //   condition: {j|Dobry|j},
// //   //   phoneNumber: {j|+48 890 300 345|j},
// //   //   avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),
// //   //   lastVisit: Some({j|22.11.2020 15:30|j}),
// //   // },
// // |];

[@react.component]
let make = () => {
  let (creatorVisible, setCreatorVisible) = React.useState(_ => false);
  let (firstName, setFirstName) = React.useState(_ => "");
  let (lastName, setLastName) = React.useState(_ => "");
  let (phoneNumber, setPhoneNumber) = React.useState(_ => "");

  let (disease, setDisease) = React.useState(_ => "");

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
    </SideNav>
  </Page>;
};
