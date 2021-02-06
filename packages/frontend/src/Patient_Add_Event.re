module Query = [%graphql
  {|
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
|}
];

module AddEvent = {
  type values = {
    strength: string,
    notes: string,
  };

  [@react.component]
  let make = (~onClose, ~patientId) => {
    let symptom = Select.use();

    let (values, setValues) = React.useState(_ => {strength: "", notes: ""});

    let (feeling, setFeeling) = React.useState(_ => "");

    let (query, result) = Query.useLazy();

    React.useEffect1(
      () => {
        switch (patientId) {
        | Some(patientId) => query({id: patientId})
        | None => ()
        };
        None;
      },
      [|patientId|],
    );

    let symptoms =
      switch (result) {
      | Executed({data: Some({symptoms})}) =>
        symptoms->Array.map(s => Select.{value: s.id, label: s.name})
      | _ => [||]
      };
    <div
      className="w-64 bg-white shadow-xl rounded-xl fixed top-12 right-12 py-8 px-6 border border-gray-200"
      style={ReactDOM.Style.make(~width="450px", ())}>
      <div className="text-2xl text-gray-600 mb-4 flex justify-between">
        <Text> {j|Zaktualizuj przebieg choroby|j} </Text>
        <Button.Nav onClick={_ => onClose()}>
          <Icons.Plus className="transform rotate-45" size="18" />
        </Button.Nav>
      </div>
      <Input.Wrap>
        <Select
          placeholder={j|Wybierz symptom|j}
          value={symptom.value}
          search={symptom.search}
          visible={symptom.visible}
          onVisibleChange={symptom.setVisible}
          onChange={symptom.setValue}
          onSearchChange={symptom.setSearch}
          loading={
            switch (result) {
            | Executed({loading: true}) => true
            | _ => false
            }
          }
          options=symptoms
          icon={<Icons.Thermometer />}
        />
      </Input.Wrap>
      <Input.Wrap>
        <Input
          value={values.strength}
          onChange={strength => setValues(values => {...values, strength})}
          placeholder={j|Siła objawu|j}
        />
      </Input.Wrap>
      <Input.Wrap>
        <Input.Textarea
          placeholder={j|Dodatkowe informacje|j}
          value={values.notes}
          onChange={notes => setValues(values => {...values, notes})}
        />
      </Input.Wrap>
      <div className="flex justify-end">
        <Button.CTA> <Text> {j|Dodaj informację|j} </Text> </Button.CTA>
      </div>
      <div className="text-2xl text-gray-600 mb-4 mt-8">
        <Text> {j|Samopoczucie|j} </Text>
      </div>
      <Input.Wrap>
        <Input
          value=feeling
          onChange={v => setFeeling(_ => v)}
          placeholder={j|Samopoczucie|j}
        />
      </Input.Wrap>
      <div className="flex justify-end">
        <Button.CTA> <Text> {j|Zapisz|j} </Text> </Button.CTA>
      </div>
    </div>;
  };
};

[@react.component]
let make = (~patientId) => {
  let (visible, setVisible) = React.useState(_ => false);
  <div className="fixed bottom-12 right-12">
    {visible
       ? <AddEvent patientId onClose={_ => setVisible(_ => false)} />
       : React.null}
    <Button.SmallRound
      className=Cn.(
        "w-16 h-16 transform transition-transform" + on("rotate-45", visible)
      )
      onClick={_ => setVisible(x => !x)}
      icon={<Icons.Plus size="32" />}
    />
  </div>;
};
