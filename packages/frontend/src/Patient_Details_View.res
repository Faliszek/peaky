open Patient_Query.Query

module Section = {
  @react.component
  let make = (~title, ~icon, ~children, ~button=?) => <>
    <div className="flex items-center justify-between text-2xl text-gray-700 mb-8 mt-12 pb-4">
      <div className="flex items-center">
        <div className="p-2 cursor-pointer rounded-lg  mr-4 border-2 border-green-50 bg-green-50">
          <span className="text-green-400"> icon </span>
        </div>
        <span className="text-gray-500"> <Text> title </Text> </span>
      </div>
      {switch button {
      | Some(button) => button
      | None => React.null
      }}
    </div>
    children
  </>
}

module Symptom_Add = {
  @react.component
  let make = (~patientId, ~visible, ~onClose, ~callMode) => {
    let (symptomName, setSymptomName) = React.useState(_ => "")
    let (circumstances, setCircumstances) = React.useState(_ => "")
    let (date, setDate) = React.useState(_ => "")
    let (occurences, setOccurences) = React.useState(_ => "")
    let (description, setDescription) = React.useState(_ => "")
    let (causedBy, setCausedBy) = React.useState(_ => "")
    let (color, setColor) = React.useState(_ => "")
    let (notes, setNotes) = React.useState(_ => "")

    let (createSymptom, resultSymptom) = Symptom_Mutation.Mutation.use(
      ~refetchQueries=[Patient_Query.Query.refetchQueryDescription({id: patientId})],
      (),
    )
    !callMode
      ? <Modal
          visible
          loading=resultSymptom.loading
          onVisibleChange={_ => onClose()}
          onOk={_ =>
            createSymptom({
              name: symptomName,
              occurences: occurences,
              description: description,
              causedBy: causedBy,
              notes: notes,
              patientId: patientId,
              date: date,
              circumstances: circumstances,
              color: color,
            })->Request.onFinish(~onOk=_ => onClose(), ~onError=Js.log)}>
          <Input.Wrap>
            <Input placeholder=j`Nazwa` value=symptomName onChange={v => setSymptomName(_ => v)} />
          </Input.Wrap>
          <Input.Wrap>
            <Input
              placeholder=j`Okoliczności pojawienia się`
              value=circumstances
              onChange={v => setCircumstances(_ => v)}
            />
          </Input.Wrap>
          <Input.Wrap>
            <Input
              placeholder=j`Data pierwszego wystąpienia` value=date onChange={v => setDate(_ => v)}
            />
          </Input.Wrap>
          <Input.Wrap>
            <Input
              placeholder=j`Częstotliwość występowania`
              value=occurences
              onChange={v => setOccurences(_ => v)}
            />
          </Input.Wrap>
          <Input.Wrap>
            <Input placeholder=j`Opis` value=description onChange={v => setDescription(_ => v)} />
          </Input.Wrap>
          <Input.Wrap>
            <Input
              placeholder=j`Spowodowany przez` value=causedBy onChange={v => setCausedBy(_ => v)}
            />
          </Input.Wrap>
          <Input.Wrap>
            <Input.Textarea
              placeholder=j`Dodatkowe informacje` value=notes onChange={v => setNotes(_ => v)}
            />
          </Input.Wrap>
          <Color_Picker value=color onChange={v => setColor(_ => v)} />
        </Modal>
      : React.null
  }
}

module Legend = {
  @react.component
  let make = (~title, ~color) =>
    <div className="flex justify-center items-center flex-col w-1/6">
      <div
        style={ReactDOM.Style.make(
          ~backgroundColor=color,
          ~width="100%",
          ~height="3px",
          ~borderRadius="10px",
          (),
        )}
      />
      <div className="text-sm text-gray-800 mt-2"> <Text> title </Text> </div>
    </div>
}

type t = {
  id: string,
  color: string,
  data: array<Chart.dataLine>,
}

@react.component
let make = (~id, ~callMode=false) => {
  let (visible, setVisible) = React.useState(_ => false)

  let query = Calendar_Query.Query.use()
  let patientQuery = Patient_Query.Query.use({id: id})

  let (createVisit, result) = Visit_Mutation.Mutation.use(
    ~refetchQueries=[Calendar_Query.Query.refetchQueryDescription()],
    (),
  )

  let name = callMode
    ? "-"
    : patientQuery.data
      ->Option.map(({patient}) => patient.firstName ++ (" " ++ patient.lastName))
      ->Option.getWithDefault("")

  let (width, setWidth) = React.useState(_ => None)
  let (modalVisible, setModalVisible) = React.useState(_ => false)

  let (creatorVisible, setCreatorVisible) = React.useState(_ => false)

  <Page title={callMode ? "" : j`Detale: $name`} hasBackButton={callMode ? false : true}>
    <Page.Block>
      {switch patientQuery {
      | {loading: true} => <Spinner />
      | {data: Some({patient})} =>
        let {firstName, lastName, phoneNumber, disease, lastVisit, color} = patient

        <div className="flex items-center">
          <div className="flex flex-1 items-center ml-4">
            <Avatar
              firstName={callMode ? "X" : firstName}
              lastName={callMode ? "X" : lastName}
              size=#big
              color
            />
            <Patient_Block.Info
              name={callMode ? "" : name}
              lastVisit
              disease
              phoneNumber={callMode ? "" : phoneNumber}
            />
          </div>
          {callMode
            ? React.null
            : <div className="ml-16 flex  flex-1 flex-col items-start justify-start">
                <Button.CTA
                  onClick={_ => setVisible(_ => true)}
                  icon={<Icons.Plus className="mr-4" />}
                  type_=#ghost>
                  <Text> j`Dodaj wizytę` </Text>
                </Button.CTA>
                <div className="h-4" />
                <Button.CTA
                  icon={<Icons.Thermometer className="mr-4" />}
                  onClick={_ => setCreatorVisible(_ => true)}>
                  <Text> j`Aktualizuj przebieg leczenia` </Text>
                </Button.CTA>
              </div>}
        </div>
      | _ => React.null
      }}
    </Page.Block>
    <Section title=j`Przebieg choroby` icon={<Icons.BarChart />}>
      {switch patientQuery {
      | {loading: true} => <Spinner />
      | {data: Some({feelings, patientEvents, symptoms})} =>
        let feelings = feelings->Array.map(f => {
          open Chart
          {x: f.timestamp, y: f.value->float_of_string}
        })

        let symptomIds = patientEvents->Array.reduce([], (acc, {symptompId}) =>
          switch acc {
          | acc if acc->Array.keep(id => id == symptompId)->Array.get(0)->Option.isSome => acc
          | acc => acc->Array.concat([symptompId])
          }
        )

        let symptomsData: array<t> = symptomIds->Array.reduce([], (acc, id) =>
          acc->Array.concat([
            {
              id: id,
              color: symptoms
              ->Array.keep(s => s.id == id)
              ->Array.get(0)
              ->Option.map(s => s.color)
              ->Option.getWithDefault(""),
              data: patientEvents
              ->Array.keep(e => e.symptompId == id)
              ->Array.map(e => {
                open Chart
                {x: e.timestamp, y: e.feeling}
              }),
            },
          ])
        )
        <div>
          <div
            className="flex items-center gap-8"
            ref={ReactDOM.Ref.callbackDomRef(el =>
              setWidth(_ => el->Js.Nullable.toOption->Option.map(el => el->HTMLElement.offsetWidth))
            )}>
            <Chart.XYPlot width={width->Option.getWithDefault(600.0)} height=300.0>
              <Chart.HorizontalGridLines style={ReactDOM.Style.make(~stroke="#E2E8F0", ())} />
              <Chart.XAxis
                attr="x"
                attrAxis="y"
                orientation="bottom"
                tickFormat={v => v->Time.format("dd.MM.yy")}
                tickTotal=8
              />
              <Chart.YAxis attr="y" attrAxis="x" orientation="left" />
              <Chart.LineSeries
                curve=#curveMonotoneX
                strokeStyle=#solid
                data=feelings
                opacity=1.0
                style={ReactDOM.Style.make(~strokeWidth="5px", ~fill="none", ~stroke="green", ())}
              />
              {symptomsData
              ->Array.map(s =>
                <Chart.LineSeries
                  key=s.id
                  curve=#curveMonotoneX
                  strokeStyle=#solid
                  data=s.data
                  opacity=1.0
                  style={ReactDOM.Style.make(~strokeWidth="5px", ~fill="none", ~stroke=s.color, ())}
                />
              )
              ->React.array}
            </Chart.XYPlot>
          </div>
          <div className="flex gap-10 px-8 pt-16 pb-8 justify-center">
            <Legend key="feeling" title=j`Ogólne samopoczucie` color="green" />
            {symptoms->Array.map(s => <Legend key=s.id title=s.name color=s.color />)->React.array}
          </div>
        </div>

      | _ => React.null
      }}
    </Section>
    <Section
      title=j`Symptomy`
      icon={<Icons.Thermometer />}
      button={callMode
        ? React.null
        : <Button.CTA onClick={_ => setModalVisible(_ => true)}>
            <Text> j`Dodaj symptom` </Text>
          </Button.CTA>}>
      <Symptom_Add
        visible=modalVisible onClose={_ => setModalVisible(_ => false)} patientId=id callMode
      />
      {switch patientQuery {
      | {loading: true} => <Spinner />
      | {data: Some({symptoms})} if symptoms->Array.size == 0 =>
        <NoData title=j`Brak objawów` text=j`Pacjent zdrowy` />
      | {data: Some({symptoms})} => <> <Symptoms_Table symptoms /> </>
      | _ => React.null
      }}
    </Section>
    {switch query {
    | {data: Some(data)} =>
      <Calendar_AddVisit
        onClose={_ => setVisible(_ => false)}
        visible
        date=None
        patientId=id
        loading=result.loading
        patients=data.patients
        onSubmit={(~patientId, ~from_, ~to_, ~notes) =>
          createVisit({
            patientId: patientId,
            from_: from_,
            to_: to_,
            notes: Some(notes),
          })->Request.onFinish(~onOk=_ => setVisible(_ => false), ~onError=_ => ())}
      />
    | _ => React.null
    }}
    {creatorVisible
      ? <Patient_Add_Event.AddEvent
          patientId=Some(id) onClose={_ => setCreatorVisible(_ => false)}
        />
      : React.null}
  </Page>
}
