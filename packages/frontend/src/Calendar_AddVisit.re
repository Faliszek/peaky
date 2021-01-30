type patients = array(Frontend.Calendar_Query.Query.Query_inner.t_patients);
let toSelectOptions = (patients: patients) => {
  Select.(
    patients->Array.map(p =>
      {value: p.id, label: p.firstName ++ " " ++ p.lastName}
    )
  );
};
[@react.component]
let make =
    (
      ~visible,
      ~onClose,
      ~patients: array(Frontend.Calendar_Query.Query.Query_inner.t_patients),
    ) => {
  let patient = Select.use();
  // let a = data + 2;
  <SideNav title={j|Dodaj wizytę|j} visible onClose>
    <Input.Wrap>
      <Select
        value={patient.value}
        search={patient.search}
        visible={patient.visible}
        onChange={patient.setValue}
        onSearchChange={patient.setSearch}
        onVisibleChange={patient.setVisible}
        placeholder={j|Wybierz pacjenta|j}
        icon={<Icons.User size="20" />}
        options={patients->toSelectOptions}
      />
    </Input.Wrap>
    <Input.Wrap label="Od">
      <Input
        value=""
        onChange={_ => ()}
        placeholder={j|00:00|j}
        icon={<Icons.Clock size="20" />}
      />
    </Input.Wrap>
    <Input.Wrap label="Do">
      <Input
        value=""
        onChange={_ => ()}
        placeholder={j|00:00|j}
        icon={<Icons.Clock size="20" />}
      />
    </Input.Wrap>
    <Input.Wrap> <Input.Textarea placeholder={j|Notatki|j} /> </Input.Wrap>
    <Button.Row>
      <Button.CTA> <Text> {j|Dodaj wizytę|j} </Text> </Button.CTA>
    </Button.Row>
  </SideNav>;
};
