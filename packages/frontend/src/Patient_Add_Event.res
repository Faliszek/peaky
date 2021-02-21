module Query = %graphql(`
    query Patient($id: String!) {


        symptoms(patientId: $id) {
          id
          name
          date
          circumstances
          description
          occurences
          causedBy
          notes
        }
}
`)

module AddFeeling = %graphql(`

mutation AddFeeling($patientId: String!, $value: String!, $timestamp: Float!){
  addFeeling(patientId: $patientId, value: $value, timestamp: $timestamp){
    id
    patientId
    value
    timestamp
  }
}
`)

module AddEventMutation = %graphql(`
mutation AddEventMutation($patientId: String!, $symptomId: String!, $feeling: Float!, $timestamp: Float!) {
  addPatientEvent(patientId: $patientId, symptompId: $symptomId, feeling: $feeling, timestamp: $timestamp){
    id
    symptompId
    feeling
    timestamp
  }
}
`)

module AddEvent = {
  type values = {
    strength: string,
    notes: string,
  }

  @react.component
  let make = (~onClose, ~patientId) => {
    let symptom = Select.use()

    let (values, setValues) = React.useState(_ => {strength: "", notes: ""})

    let (feeling, setFeeling) = React.useState(_ => "")

    let (query, result) = Query.useLazy()

    React.useEffect1(() => {
      switch patientId {
      | Some(patientId) => query({id: patientId})
      | None => ()
      }
      None
    }, [patientId])

    let symptoms = switch result {
    | Executed({data: Some({symptoms})}) =>
      symptoms->Array.map(s => {
        open Select
        {value: s.id, label: s.name}
      })
    | _ => []
    }

    let (addEvent, addEventResult) = AddEventMutation.use()

    let (addFeeling, addFeelingResult) = AddFeeling.use()

    <div
      className="w-64 bg-white shadow-xl rounded-xl fixed top-12 right-12 py-8 px-6 border border-gray-200"
      style={ReactDOM.Style.make(~width="450px", ())}>
      <div className="text-2xl text-gray-600 mb-4 flex justify-between">
        <Text> `Zaktualizuj przebieg choroby` </Text>
        <Button.Nav onClick={_ => onClose()}>
          <Icons.Plus className="transform rotate-45" size="18" />
        </Button.Nav>
      </div>
      <Input.Wrap>
        <Select
          placeholder=`Wybierz symptom`
          value=symptom.value
          search=symptom.search
          visible=symptom.visible
          onVisibleChange=symptom.setVisible
          onChange=symptom.setValue
          onSearchChange=symptom.setSearch
          loading={switch result {
          | Executed({loading: true}) => true
          | _ => false
          }}
          options=symptoms
          icon={<Icons.Thermometer />}
        />
      </Input.Wrap>
      <Input.Wrap>
        <Input
          value=values.strength
          onChange={strength => setValues(values => {...values, strength: strength})}
          placeholder=`Siła objawu`
        />
      </Input.Wrap>
      <Input.Wrap>
        <Input.Textarea
          placeholder=`Dodatkowe informacje`
          value=values.notes
          onChange={notes => setValues(values => {...values, notes: notes})}
        />
      </Input.Wrap>
      <div className="flex justify-end">
        <Button.CTA
          loading=addEventResult.loading
          onClick={_ =>
            switch (patientId, symptom.value) {
            | (Some(patientId), Some({value: symptom})) =>
              addEvent(
                ~refetchQueries=[
                  Patient_Query.Query.refetchQueryDescription({
                    id: patientId,
                  }),
                  Query.refetchQueryDescription({id: patientId}),
                ],
                {
                  patientId: patientId,
                  symptomId: symptom,
                  feeling: values.strength->float_of_string,
                  timestamp: Js.Date.now(),
                },
              )->ignore
            | _ => ()
            }}>
          <Text> `Dodaj informację` </Text>
        </Button.CTA>
      </div>
      <div className="text-2xl text-gray-600 mb-4 mt-8"> <Text> `Samopoczucie` </Text> </div>
      <Input.Wrap>
        <Input value=feeling onChange={v => setFeeling(_ => v)} placeholder=`Samopoczucie` />
      </Input.Wrap>
      <div className="flex justify-end">
        <Button.CTA
          loading=addFeelingResult.loading
          onClick={_ =>
            switch patientId {
            | Some(patientId) =>
              addFeeling(
                ~refetchQueries=[
                  Patient_Query.Query.refetchQueryDescription({
                    id: patientId,
                  }),
                  Query.refetchQueryDescription({id: patientId}),
                ],
                {patientId: patientId, timestamp: Js.Date.now(), value: feeling},
              )->ignore
            | _ => ()
            }}>
          <Text> `Zapisz` </Text>
        </Button.CTA>
      </div>
    </div>
  }
}

@react.component
let make = (~patientId) => {
  let (visible, setVisible) = React.useState(_ => false)
  <div className="fixed bottom-12 right-12">
    {visible ? <AddEvent patientId onClose={_ => setVisible(_ => false)} /> : React.null}
    <Button.SmallRound
      className={
        open Cn
        "w-16 h-16 transform transition-transform" + on("rotate-45", visible)
      }
      onClick={_ => setVisible(x => !x)}
      icon={<Icons.Plus size="32" />}
    />
  </div>
}
