let exportPath = %raw(`
function(canvas, cb) {
  if(canvas) {
    canvas.exportSvg().then(data => cb(data))
  }
}
`)

@react.component
let make = (
  ~patientId,
  ~callerId,
  ~myId,
  ~color,
  ~onChange,
  ~saveElCanvas,
  ~data as canvases: array<Peer.Connection.data>,
) => {
  let (width, setWidth) = React.useState(_ => "400")
  let (height, setHeight) = React.useState(_ => "400")

  let amICaller = myId == callerId

  let canvasEl = React.useRef(Js.Nullable.null)

  let (data, setData) = React.useState(_ => [])

  let waitForData = Timeout.useDebounce(data, 200)

  let debouncedData = waitForData->Array.get(0)

  React.useEffect1(() => {
    exportPath(canvasEl.current, onChange)->ignore
    saveElCanvas(canvasEl.current)
    None
  }, [debouncedData])

  Js.log(canvases)
  <div className="relative">
    <div
      ref={ReactDOM.Ref.callbackDomRef(el =>
        el
        ->Js.Nullable.toOption
        ->Option.map(el => Timeout.set(() => {
            setWidth(_ => el->HTMLElement.offsetWidth->Js.Float.toString ++ "px")
            setHeight(_ => el->HTMLElement.offsetHeight->Js.Float.toString ++ "px")
          }, 100))
        ->ignore
      )}>
      {switch (amICaller, patientId) {
      | (true, None) =>
        <NoData
          title=j`Wybierz pacjenta`
          text=j`Dane wrażliwe nie zostaną wyświetlane dla innych uczestników`
          icon={<Icons.AlertCircle size="64" />}
        />
      | (_, Some(patientId)) => <Patient_Details_View id=patientId callMode=true />
      | (false, _) =>
        <NoData
          title=j`Prowadzący nie wybrał jeszcze pacjenta`
          text=j`Po wybraniu pacjenta przez prowadzącego, tutaj pojawi się widok przebiegu choroby`
          icon={<Icons.AlertCircle size="64" />}
        />
      }}
    </div>
    {canvases
    ->Array.map(x =>
      x.id == myId
        ? React.null
        : <div key=x.id className="absolute w-full h-full top-0 left-0">
            <div dangerouslySetInnerHTML={"__html": x.svg} />
          </div>
    )
    ->React.array}
    <div className="absolute w-full h-full top-0 left-0 shadow-xl">
      <CanvasDraw
        ref={ReactDOM.Ref.domRef(canvasEl)}
        height
        width
        style={ReactDOM.Style.make(~border="none", ())}
        background="transparent"
        strokeColor=color
        onUpdate={data => setData(_ => data)}
        withTimestamp=true
      />
    </div>
  </div>
}
