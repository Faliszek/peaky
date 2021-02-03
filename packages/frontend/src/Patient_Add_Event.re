module AddEvent = {
  type values = {
    strength: string,
    notes: string,
  };

  [@react.component]
  let make = (~symptoms) => {
    let symptom = Select.use();

    let (values, setValues) = React.useState(_ => {strength: "", notes: ""});

    let (feeling, setFeeling) = React.useState(_ => "");

    <div
      className="w-64 bg-white shadow-xl rounded-xl fixed top-12 right-12 py-8 px-6 border border-gray-200"
      style={ReactDOM.Style.make(~width="450px", ())}>
      <div className="text-2xl text-gray-600 mb-4">
        <Text> {j|Zaktualizuj przebieg choroby|j} </Text>
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
let make = () => {
  let (visible, setVisible) = React.useState(_ => false);
  <div className="fixed bottom-12 right-12">
    {visible ? <AddEvent symptoms=[||] /> : React.null}
    <Button.SmallRound
      className=Cn.(
        "w-16 h-16 transform transition-transform" + on("rotate-45", visible)
      )
      onClick={_ => setVisible(x => !x)}
      icon={<Icons.Plus size="32" />}
    />
  </div>;
};
