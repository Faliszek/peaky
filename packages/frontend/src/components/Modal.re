[@react.component]
let make =
    (
      ~visible,
      ~onVisibleChange,
      ~title={j|Dodaj symptom|j},
      ~children=React.null,
      ~onOk=_ => (),
    ) => {
  let modal =
    visible
      ? <div
          className="w-screen h-screen fixed top-0 left-0 z-10 flex items-center justify-center"
          style={ReactDOM.Style.make(~backgroundColor="rgba(0,0,0,0.1)", ())}>
          <div
            style={ReactDOM.Style.make(~width="600px", ())}
            className="w-64 bg-white shadow-xl rounded-xl px-6 border border-gray-200 py-8 ">
            <div className="text-2xl text-gray-600 mb-4">
              <Text> title </Text>
            </div>
            <div> children </div>
            <div className="flex justify-end gap-3">
              <Button.CTA type_=`ghost onClick={_ => onVisibleChange(false)}>
                <Text> {j|Anuluj|j} </Text>
              </Button.CTA>
              <Button.CTA onClick={_ => onOk()}>
                <Text> {j|Dodaj|j} </Text>
              </Button.CTA>
            </div>
          </div>
        </div>
      : React.null;

  switch (ReactDOM.querySelector("body")) {
  | Some(el) => ReactDOM.createPortal(modal, el)

  | None => React.null
  };
};
