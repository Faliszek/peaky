let exportPath = [%bs.raw
  {|
function(canvas, cb) {
  if(canvas) {
    canvas.exportSvg().then(data => cb(data))
  }
}
|}
];

[@react.component]
let make =
    (
      ~patientId,
      ~callerId,
      ~myId,
      ~color,
      ~onChange,
      ~saveElCanvas,
      ~userIds,
      ~data as canvases: array(Peer.Connection.data),
    ) => {
  let (width, setWidth) = React.useState(_ => "400");
  let (height, setHeight) = React.useState(_ => "400");

  let amICaller = myId != callerId;

  let canvasEl = React.useRef(Js.Nullable.null);

  let (data, setData) = React.useState(_ => [||]);

  let [|debouncedData, _|] = Timeout.useDebounce(data, 200);

  React.useEffect1(
    () => {
      Js.log2("updated data", canvasEl);
      exportPath(canvasEl.current, onChange)->ignore;
      saveElCanvas(canvasEl.current);
      None;
    },
    [|debouncedData|],
  );
  <div className="w-full h-full relative">
    <div
      ref={ReactDOM.Ref.callbackDomRef(el =>
        el
        ->Js.Nullable.toOption
        ->Option.map(el => {
            Timeout.set(
              () => {
                setWidth(_ =>
                  el->HTMLElement.offsetWidth->Js.Float.toString ++ "px"
                );
                setHeight(_ =>
                  el->HTMLElement.offsetHeight->Js.Float.toString ++ "px"
                );
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
    {canvases
     ->Array.map(x =>
         x.id == myId
           ? React.null
           : <div className="absolute w-full h-full top-0 left-0">
               <div dangerouslySetInnerHTML={"__html": x.svg} />
             </div>
       )
     ->React.array}
    <div className="absolute w-full h-full top-0 left-0">
      <CanvasDraw
        ref={ReactDOM.Ref.domRef(canvasEl)}
        height
        width
        background="transparent"
        strokeColor=color
        onUpdate={data => setData(_ => data)}
        withTimestamp=true
      />
    </div>
  </div>;
};
