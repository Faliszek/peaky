type patients = array(Frontend.Calendar_Query.Query.Query_inner.t_patients);
let toSelectOptions = (patients: patients) => {
  Select.(
    patients->Array.map(p =>
      {value: p.id, label: p.firstName ++ " " ++ p.lastName}
    )
  );
};

let toMinutes = value => {
  let range = Js.String2.split(value, ":");
  let hour = range->Array.get(0);
  let minutes = range->Array.get(1);
  switch (hour, minutes) {
  | (Some(hour), Some(minutes)) =>
    hour->int_of_string * 60 + minutes->int_of_string
  | _ => 0
  };
};

let computeDate = (~from_, ~to_, ~date) => {
  switch (date) {
  | Some(date) =>
    let from_ = from_->toMinutes;
    let to_ = to_->toMinutes;
    (
      date
      ->Time.startOfDay
      ->Time.addMinutes(from_)
      ->Time.getTime
      ->Js.Float.toString,
      date
      ->Time.startOfDay
      ->Time.addMinutes(to_)
      ->Time.getTime
      ->Js.Float.toString,
    );
  | None => ("", "")
  };
};
[@react.component]
let make =
    (
      ~patientId=?,
      ~visible,
      ~onClose,
      ~date,
      ~patients: array(Frontend.Calendar_Query.Query.Query_inner.t_patients),
      ~loading,
      ~onSubmit,
    ) => {
  let patient = Select.use();

  let (from_, setFrom) = React.useState(_ => "");
  let (to_, setTo) = React.useState(_ => "");
  let (notes, setNotes) = React.useState(_ => "");

  React.useEffect1(
    () => {
      switch (date) {
      | Some(date) =>
        let hours = date->Time.format("HH");
        let minutes = date->Time.format("mm");

        setFrom(_ => hours ++ ":" ++ minutes);
      | None => ()
      };
      None;
    },
    [|date|],
  );

  React.useEffect2(
    () => {
      open Select;
      let p =
        patients
        ->toSelectOptions
        ->Array.keep(p => Some(p.value) == patientId)
        ->Array.get(0);

      switch (p) {
      | Some(p) =>
        patient.setValue(Some(p));
        patient.setSearch(p.label);
      | None => ()
      };

      None;
    },
    (patientId, patients),
  );

  Js.log(patient);

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
        value=from_
        onChange={v => setFrom(_ => v)}
        placeholder={j|00:00|j}
        icon={<Icons.Clock size="20" />}
      />
    </Input.Wrap>
    <Input.Wrap label="Do">
      <Input
        value=to_
        onChange={v => setTo(_ => v)}
        placeholder={j|00:00|j}
        icon={<Icons.Clock size="20" />}
      />
    </Input.Wrap>
    <Input.Wrap>
      <Input.Textarea
        placeholder={j|Notatki|j}
        value=notes
        onChange={v => setNotes(_ => v)}
      />
    </Input.Wrap>
    <Button.Row>
      <Button.CTA
        loading
        onClick={_ => {
          open Select;
          let (from_, to_) = computeDate(~from_, ~to_, ~date);
          switch (patient.value) {
          | Some({value}) =>
            onSubmit(~patientId=value, ~from_, ~to_, ~notes);
            setNotes(_ => "");
            setTo(_ => "");
            setFrom(_ => "");
            patient.setValue(None);
            patient.setSearch("");

          | None => ()
          };
        }}>
        <Text> {j|Dodaj wizytę|j} </Text>
      </Button.CTA>
    </Button.Row>
  </SideNav>;
};
