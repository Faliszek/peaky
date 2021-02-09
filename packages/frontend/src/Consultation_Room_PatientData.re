[@react.component]
let make =
    (~patientId, ~callerId, ~userIds, ~peer, ~myId, ~color, ~setPatientId) => {
  let (width, setWidth) = React.useState(_ => None);
  let (height, setHeight) = React.useState(_ => None);
  let (data, setData) = React.useState(_ => "");

  // useData(
  //   ~myId,
  //   ~callerId,
  //   ~userIds,
  //   ~peer,
  //   ~onReceiveData=
  //     data => {
  //       Js.log2(
  //         "RECEIVE",
  //         data,
  //         // setPatientId(Some(data.patientId));
  //         // setData(_ => data.data);
  //       )
  //     },
  //   ~data,
  //   ~patientId,
  // );

  React.useEffect1(
    () => {
      if (myId == callerId) {
        setData(_ => "")->ignore;
      } else {
        ();
      };

      None;
    },
    [|patientId|],
  );

  let amICaller = myId != callerId;
  <div className="w-full h-full relative">
    <div
      ref={ReactDOM.Ref.callbackDomRef(el =>
        el
        ->Js.Nullable.toOption
        ->Option.map(el => {
            Timeout.set(
              () => {
                setWidth(_ => Some(el->HTMLElement.offsetWidth));
                setHeight(_ => Some(el->HTMLElement.offsetHeight));
              },
              1000,
            )
          })
        ->ignore
      )}>
      {switch (amICaller, patientId) {
       | (_, Some(patientId)) =>
         <Patient_Details_View id=patientId callMode=true />
       | (true, _) =>
         <Text> {j|Prowadzący nie wybrał jeszcze pacjenta|j} </Text>

       | _ => React.null
       }}
    </div>
    <div className="absolute w-full h-full top-0 left-0">
      {switch (height, width, patientId) {
       | (Some(height), Some(width), Some(patientId)) =>
         <CanvasDraw
           onChange={v => {
             let data = v.getSaveData();
             setData(_ => data);
           }}
           gridColor="transparent"
           backgroundColor="transparent"
           hideGrid=true
           brushColor=color
           canvasHeight=height
           canvasWidth=width
           brushRadius=4.0
           saveData=data
           immediateLoading=true
         />
       | _ => React.null
       }}
    </div>
  </div>;
};
