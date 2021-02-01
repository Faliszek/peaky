open Patient_Query.Query;

module Section = {
  [@react.component]
  let make = (~title, ~icon, ~children, ~button=?) => {
    <>
      <div
        className="flex items-center justify-between text-2xl text-gray-700 mb-8 mt-12 pb-4">
        <div className="flex items-center">
          <div
            className="p-2 cursor-pointer rounded-lg  mr-4 border-2 border-green-50 bg-green-50">
            <span className="text-green-400"> icon </span>
          </div>
          <span className="text-gray-500"> <Text> title </Text> </span>
        </div>
        {switch (button) {
         | Some(button) => button
         | None => React.null
         }}
      </div>
      children
    </>;
  };
};

[@react.component]
let make = (~id: string, ~callMode=false) => {
  let (visible, setVisible) = React.useState(_ => false);

  let query = Calendar_Query.Query.use();
  let patientQuery = Patient_Query.Query.use({id: id});

  let (createVisit, result) =
    Visit_Mutation.Mutation.use(
      ~refetchQueries=[|Calendar_Query.Query.refetchQueryDescription()|],
      (),
    );

  let name =
    callMode
      ? "-"
      : patientQuery.data
        ->Option.map(({patient}) =>
            patient.firstName ++ " " ++ patient.lastName
          )
        ->Option.getWithDefault("");

  let (width, setWidth) = React.useState(_ => None);
  let (modalVisible, setModalVisible) = React.useState(_ => true);

  let (circumstances, setCircumstances) = React.useState(_ => "");
  let (date, setDate) = React.useState(_ => "");
  let (occurences, setOccurences) = React.useState(_ => "");
  let (description, setDescription) = React.useState(_ => "");
  let (causedBy, setCausedBy) = React.useState(_ => "");
  let (notes, setNotes) = React.useState(_ => "");

  <Page
    title={callMode ? "" : {j|Detale: $name|j}}
    hasBackButton={callMode ? false : true}>
    <Page.Block>
      {switch (patientQuery) {
       | {loading: true} => <Spinner />
       | {data: Some({patient})} =>
         let {firstName, lastName, phoneNumber, disease, lastVisit, color} = patient;

         <div className="flex items-center">
           <div className="flex flex-1 items-center ml-4">
             <Avatar
               firstName={callMode ? "X" : firstName}
               lastName={callMode ? "X" : lastName}
               size=`big
               color
             />
             <Patient_Block.Info
               name={callMode ? "" : name}
               lastVisit
               disease
               phoneNumber
             />
           </div>
           {callMode
              ? React.null
              : <div
                  className="ml-16 flex  flex-1 flex-col items-start justify-start">
                  <Button.CTA
                    onClick={_ => setVisible(_ => true)}
                    icon={<Icons.Plus className="mr-4" />}
                    type_=`ghost>
                    <Text> {j|Dodaj wizytę|j} </Text>
                  </Button.CTA>
                  <div className="h-4" />
                  <Button.CTA
                    icon={<Icons.Video className="mr-4" />}
                    onClick={_ => Router.(push(PatientVideoChat(id)))}>
                    <Text> {j|Rozpocznij videorozmowe|j} </Text>
                  </Button.CTA>
                </div>}
         </div>;
       | _ => React.null
       }}
    </Page.Block>
    <Section title={j|Przebieg choroby|j} icon={<Icons.BarChart />}>
      <div
        className="flex items-center gap-8"
        ref={ReactDOM.Ref.callbackDomRef(el =>
          setWidth(_ =>
            el
            ->Js.Nullable.toOption
            ->Option.map(el => el->HTMLElement.offsetWidth)
          )
        )}>
        <Chart.XYPlot
          width={width->Option.getWithDefault(600.0)} height=300.0>
          <Chart.HorizontalGridLines
            style={ReactDOM.Style.make(~stroke="#E2E8F0", ())}
          />
          <Chart.XAxis
            attr="x"
            attrAxis="y"
            orientation="bottom"
            tickFormat={v => {
              Js.log(v);
              "dupa";
            }}
          />
          <Chart.YAxis attr="y" attrAxis="x" orientation="left" />
          <Chart.LineSeries
            curve=`curveMonotoneX
            strokeStyle=`solid
            data=Chart.([|{x: 1.0, y: 1.0}, {x: 2.0, y: 2.0}|])
            opacity=1.0
            style={ReactDOM.Style.make(~strokeWidth="5px", ())}
          />
          <Chart.LineSeries
            curve=`curveMonotoneX
            strokeStyle=`solid
            data=Chart.(
              [|{x: 2.0, y: 2.0}, {x: 3.0, y: 1.0}, {x: 4.0, y: 1.5}|]
            )
            opacity=1.0
            style={ReactDOM.Style.make(~strokeWidth="5px", ~fill="none", ())}
          />
        </Chart.XYPlot>
      </div>
    </Section>
    <Section
      title={j|Symptomy|j}
      icon={<Icons.Thermometer />}
      button={
        <Button.CTA onClick={_ => setModalVisible(_ => true)}>
          <Text> {j|Dodaj symptom|j} </Text>
        </Button.CTA>
      }>
      {switch (Symptoms.symptoms) {
       | symptoms when symptoms->Array.size == 0 =>
         <NoData title={j|Brak objawów|j} text={j|Pacjent zdrowy|j} />
       | symptoms =>
         <>
           <Symptoms_Table symptoms />
           <Modal
             visible=modalVisible
             onVisibleChange={_ => setModalVisible(_ => false)}>
             <Input.Wrap>
               <Input
                 placeholder={j|Okoliczności pojawienia się|j}
                 value=circumstances
                 onChange={v => setCircumstances(_ => v)}
               />
             </Input.Wrap>
             <Input.Wrap>
               <Input
                 placeholder={j|Data pierwszego wystąpienia|j}
                 value=date
                 onChange={v => setDate(_ => v)}
               />
             </Input.Wrap>
             <Input.Wrap>
               <Input
                 placeholder={j|Częstotliwość występowania|j}
                 value=occurences
                 onChange={v => setOccurences(_ => v)}
               />
             </Input.Wrap>
             <Input.Wrap>
               <Input
                 placeholder={j|Opis|j}
                 value=description
                 onChange={v => setDescription(_ => v)}
               />
             </Input.Wrap>
             <Input.Wrap>
               <Input
                 placeholder={j|Spowodowany przez|j}
                 value=causedBy
                 onChange={v => setCausedBy(_ => v)}
               />
             </Input.Wrap>
             <Input.Wrap>
               <Input.Textarea
                 placeholder={j|Dodatkowe informacje|j}
                 value=notes
                 onChange={v => setNotes(_ => v)}
               />
             </Input.Wrap>
           </Modal>
         </>
       }}
    </Section>
    {switch (query) {
     | {data: Some(data)} =>
       <Calendar_AddVisit
         onClose={_ => setVisible(_ => false)}
         visible
         date=None
         patientId=id
         loading={result.loading}
         patients={data.patients}
         onSubmit={(~patientId, ~from_, ~to_, ~notes) =>
           createVisit({patientId, from_, to_, notes: Some(notes)})
           ->Request.onFinish(
               ~onOk=_ => setVisible(_ => false),
               ~onError=_ => (),
             )
         }
       />
     | _ => React.null
     }}
    <Patient_Add_Symptom />
  </Page>;
  // <Section title={j|Historia wizyt|j} icon={<Icons.Clock />}>
  //   {switch (patientQuery) {
  //    | {data: Some({calls})} when calls->Array.size == 0 =>
  //      <NoData
  //        title={j|Historia wizyt pusta|j}
  //        text={j|Nie prowadziłeś jeszcze konsultacji z tym pacjentem|j}
  //      />
  //    //  | {data: Some({calls})} =>
  //    //  let calls =
  //    //    calls->Array.map(c =>
  //    //      Call.fromGraphql(
  //    //        ~duration=c.duration,
  //    //        ~id=c.id,
  //    //        ~answered=c.answered,
  //    //        ~timestamp=c.timestamp,
  //    //        ~withWho=               (),
  //    //      )
  //    //    );
  //    //  <Visits_History calls callMode name />;
  //    //  React.null
  //    | {loading: true} => <Spinner />
  //    | _ => React.null
  //    }}
  // </Section>
};
