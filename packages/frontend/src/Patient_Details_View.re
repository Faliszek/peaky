open Patient;

let patient = {
  id: 1,
  firstName: {j|Adam|j},
  lastName: {j|Smith|j},
  disease: {j|Depresja|j},
  condition: {j|Dobry|j},
  avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),

  phoneNumber: {j|+48 674 300 232|j},
  lastVisit: None,
};

[@react.component]
let make = (~id) => {
  let {
    firstName,
    lastName,
    avatar,
    phoneNumber,
    disease,
    condition,
    lastVisit,
  }: Patient.t = patient;
  let name = firstName ++ " " ++ lastName;

  <Page title={j|Detale: $name|j} hasBackButton=true>
    <Page.Block>
      <div className="flex items-center">
        <div className="flex flex-1 items-center ml-4">
          <Avatar avatar firstName lastName size=`big />
          <Patient_Block.Info name condition lastVisit disease phoneNumber />
        </div>
        <div className="ml-16 flex  flex-1 flex-col items-start justify-start">
          <Button.CTA
            onClick={_ => Router.(push(PatientChat(id)))}
            icon={<Icons.Message className="mr-4" />}
            type_=`ghost>
            <Text> {j|Rozpocznij chat|j} </Text>
          </Button.CTA>
          <div className="h-4" />
          <Button.CTA
            icon={<Icons.Video className="mr-4" />}
            onClick={_ => Router.(push(PatientVideoChat(id)))}>
            <Text> {j|Rozpocznij videorozmowe|j} </Text>
          </Button.CTA>
        </div>
      </div>
    </Page.Block>
  </Page>;
};
