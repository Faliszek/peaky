module Query = [%graphql
  {|
    query Patient($id: String!) {
      patient(id: $id) {
        id
        firstName
        lastName
        phoneNumber
        disease
        lastVisit
        color
      }
}
|}
];

module Section = {
  [@react.component]
  let make = (~title, ~icon, ~children) => {
    <>
      <div
        className="flex items-center text-2xl text-gray-700 mb-8 mt-12 pb-4">
        <div
          className="p-2 cursor-pointer rounded-lg  mr-4 border-2 border-green-50 bg-green-50">
          <span className="text-green-400"> icon </span>
        </div>
        <span className="text-gray-500"> <Text> title </Text> </span>
      </div>
      children
    </>;
  };
};

[@react.component]
let make = (~id: string) => {
  let (visible, setVisible) = React.useState(_ => false);

  let query = Calendar_Query.Query.use();
  let patientQuery = Query.use({id: id});

  let (createVisit, result) =
    Visit_Mutation.Mutation.use(
      ~refetchQueries=[|Calendar_Query.Query.refetchQueryDescription()|],
      (),
    );

  let name =
    patientQuery.data
    ->Option.map(({patient}) => patient.firstName ++ " " ++ patient.lastName)
    ->Option.getWithDefault("");

  let (width, setWidth) = React.useState(_ => None);

  <Page title={j|Detale: $name|j} hasBackButton=true>
    <Page.Block>
      {switch (patientQuery) {
       | {loading: true} => <Spinner />
       | {data: Some({patient})} =>
         let {firstName, lastName, phoneNumber, disease, lastVisit}: Query.t_patient = patient;

         <div className="flex items-center">
           <div className="flex flex-1 items-center ml-4">
             <Avatar firstName lastName size=`big />
             <Patient_Block.Info name lastVisit disease phoneNumber />
           </div>
           <div
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
           </div>
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
    <Section title={j|Historia wizyt|j} icon={<Icons.Clock />}>
      {switch (Visit.calls) {
       | calls when calls->Array.size == 0 =>
         <NoData
           title={j|Historia wizyt pusta|j}
           text={j|Nie prowadziłeś jeszcze konsultacji z tym pacjentem|j}
         />
       | calls => <Visits_History calls />
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
  </Page>;
};
