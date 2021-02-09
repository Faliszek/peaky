open Patient_List_Query;
let toSelectOptions = patients => {
  Query.(
    Select.(
      patients->Array.map(p =>
        {value: p.id, label: p.firstName ++ " " ++ p.lastName}
      )
    )
  );
};

[@react.component]
let make = (~callerId, ~myId, ~userIds, ~peer) => {
  let query = Query.use();
  let patient = Select.use();

  let (patientId, setPatientId) = React.useState(_ => None);
  let (color, setColor) = React.useState(_ => "rgb(96, 165, 250)");

  let (visible, setVisible) = React.useState(_ => false);

  let callerId = "data" ++ callerId;
  let userIds = userIds->Array.map(u => "data" ++ u);

  let userIds =
    userIds->Array.concat([|callerId|])->Array.keep(u => u != myId);

  <div className="w-full h-screen flex items-center">
    {switch (query) {
     | {loading: true} => <Spinner />
     | {data: Some({patients})} =>
       <div className="h-full py-8 px-4 w-full">
         <div
           className="w-full flex gap-8 justify-between shadow-lg sticky border-bottom border-gray-300 top-0 p-4 rounded-xl z-20 bg-white">
           //  {callerId == myId  ?

             <div className="flex gap-8 justify-between">
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
               <Button.CTA
                 onClick={_ =>
                   setPatientId(_ => patient.value->Option.map(x => x.value))
                 }>
                 <Text> {j|Wybierz|j} </Text>
               </Button.CTA>
             </div>
             // : React.null}
             <div className="flex items-center">
               {[||]->Array.size != 0
                  ? <Button.CTA icon={<Icons.ArrowLeft className="mr-2" />}>
                      <Text> {j|Cofnij|j} </Text>
                    </Button.CTA>
                  : React.null}
               <Button.Nav
                 onClick={_ => setVisible(v => !v)} className="relative">
                 <span style={ReactDOM.Style.make(~color, ())}>
                   <Icons.Edit3 />
                 </span>
                 {visible
                    ? <Color_Picker
                        value=color
                        onChange={v => setColor(_ => v)}
                        className="w-48 absolute right-0 top-4 border border-gray-200 shadow-lg bg-white p-4 z-30"
                      />
                    : React.null}
               </Button.Nav>
             </div>
           </div>
         <Consultation_Room_PatientData
           peer
           patientId
           color
           myId
           userIds
           callerId
           setPatientId={v => setPatientId(_ => v)}
         />
       </div>
     | _ => React.null
     }}
  </div>;
};
