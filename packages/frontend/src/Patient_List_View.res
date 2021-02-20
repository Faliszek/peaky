module Mutation = %graphql(`
  mutation CreatePatient($firstName: String!, $lastName: String!, $phoneNumber: String!, $disease: String!, $color: String!) {
    createPatient(
      firstName: $firstName,
      lastName: $lastName,
      phoneNumber: $phoneNumber,
      disease: $disease,
      color:$color
      ){
      id
      firstName
      lastName
      phoneNumber
      disease
      color
  }
  }
`)

module ListQuery = Patient_List_Query.Query

@react.component
let make = (~callMode as _=false) => {
  let (creatorVisible, setCreatorVisible) = React.useState(_ => false)

  let queryUsers = ListQuery.use()
  let (createUser, result) = Mutation.use(~refetchQueries=[ListQuery.refetchQueryDescription()], ())
  <Page
    title="Pacjenci"
    actions={<Button.CTA
      onClick={_ => setCreatorVisible(_ => true)} icon={<Icons.Plus className="mr-4" />}>
      <Text> j`Dodaj pacjenta` </Text>
    </Button.CTA>}>
    <div>
      {switch queryUsers {
      | {loading: true} => <Spinner />
      | {data: Some(data)} if data.patients->Array.size == 0 =>
        <NoData
          buttonText=j`Dodaj pacjenta`
          buttonIcon={<Icons.Plus />}
          onButtonClick={_ => setCreatorVisible(_ => true)}
          title=j`Brak danych`
          text=j`Kliknij przycisk poniżej aby otworzyć kreator pacjenta`
        />
      | {data: Some(data)} =>
        <div className="flex flex-wrap justify-between items-stretch">
          {data.patients
          ->Array.map(patient =>
            <Patient_Block key=patient.id patient className="w-1/3 flex-auto mb-8 mr-12" />
          )
          ->React.array}
        </div>
      | _ => React.null
      }}
    </div>
    <Patient_AddPatient
      loading=result.loading
      visible=creatorVisible
      onCreate={(~firstName, ~lastName, ~phoneNumber, ~disease, ~color) =>
        createUser({
          firstName: firstName,
          lastName: lastName,
          phoneNumber: phoneNumber,
          disease: disease,
          color: color,
        })->Request.onFinish(
          ~onOk=_ => setCreatorVisible(_ => false),
          ~onError=_ => Js.log("unexpected"),
        )}
      onClose={_ => setCreatorVisible(_ => false)}
    />
  </Page>
}
