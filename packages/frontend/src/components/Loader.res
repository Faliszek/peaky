type document = {body: Dom.element}
@val external document: document = "document"
@val external setTimeout: (unit => unit, int) => int = "setTimeout"
@val external clearTimeout: int => unit = "clearTimeout"

type state =
  | StartLoading
  | FinishLoading
  | Idle

let toState = (~prevState, ~loading) =>
  switch (prevState, loading) {
  | (false, true) => StartLoading
  | (true, false) => FinishLoading
  | _ => Idle
  }
let useAnimate = loading => {
  let (prevState, setPrevState) = React.useState(_ => loading)
  let state = React.useMemo2(() => toState(~prevState, ~loading), (prevState, loading))

  let (cn, setCn) = React.useState(_ => 0.0)

  React.useEffect1(() => {
    setPrevState(_ => loading)
    None
  }, [loading])

  React.useEffect1(() => {
    switch state {
    | StartLoading =>
      setTimeout(() => setCn(_ => 0.0), 50)->ignore
      setTimeout(() => setCn(_ => 0.25), 100)->ignore
      setTimeout(() => setCn(_ => 0.75), 125)->ignore
    | FinishLoading =>
      setCn(_ => 1.0)

      setTimeout(() => setCn(_ => 0.0), 50)->ignore
    | _ => ()
    }
    None
  }, [state])

  cn->Js.Float.toString
}
@react.component
let make = (~loading=false) => {
  let scaleX = useAnimate(loading)

  ReactDOM.createPortal(
    <div className="fixed top-0 left-0 h-1 w-full z-20 scale">
      <div
        style={ReactDOM.Style.make(~transform=`scaleX($scaleX)`, ())}
        className="bg-green-500 h-full w-full transform transition-transform origin-left "
      />
    </div>,
    document.body,
  )
}
