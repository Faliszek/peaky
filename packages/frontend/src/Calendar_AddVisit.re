[@react.component]
let make = (~visible, ~onClose) => {
  let patient = Select.use();

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
        options=[|
          {value: "1", label: {j|Paweł Falisz|j}},
          {value: "2", label: {j|Weronika Falisz|j}},
        |]
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
