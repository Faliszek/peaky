module Wrap = {
  [@react.component]
  let make = (~children, ~label=?) => {
    switch (label) {
    | Some(label) =>
      <div className="mb-6">
        <span className=" text-lg mb-1 ml-2"> <Text> label </Text> </span>
        children
      </div>
    | None => <div className="mb-6"> children </div>
    };
  };
};

let focusCn = "outline-none focus:ring-2 focus:ring-green-400 focus:border-green-400";

module Textarea = {
  [@react.component]
  let make = (~placeholder, ~ref_=?, ~value, ~onChange) => {
    <textarea
      ref=?ref_
      placeholder
      value
      onChange={e => onChange(e->ReactEvent.Form.target##value)}
      className=Cn.(
        "p-4  w-full rounded-lg border text-lg text-gray-700  mr-4" + focusCn
      )
    />;
  };
};

let callSome = func => func->Option.map(f => f())->ignore;

[@react.component]
let make =
    (
      ~value,
      ~onChange,
      ~placeholder,
      ~type_=?,
      ~icon=?,
      ~onFocus=?,
      ~onBlur=?,
      ~zIndex=?,
    ) => {
  let (focus, setFocus) = React.useState(_ => false);

  let style =
    switch (zIndex) {
    | Some(index) =>
      Some(ReactDOMRe.Style.make(~zIndex=index->Js.Int.toString, ()))
    | None => None
    };
  let input = (~cn=?, ()) =>
    <input
      spellCheck=false
      value
      onChange={e => onChange(e->ReactEvent.Form.target##value)}
      onFocus={_ => {
        setFocus(_ => true);
        onFocus->callSome;
      }}
      onBlur={_ => {
        setFocus(_ => false);

        onBlur->callSome;
      }}
      placeholder
      className=Cn.(
        "shadow-md  text-gray-700  border border-gray-100 rounded-lg px-4 py-2 text-lg w-full h-12"
        + mapSome(cn, x => x)
        + focusCn
      )
      ?type_
    />;

  switch (icon) {
  | Some(icon) =>
    <div className="flex relative " ?style>
      <span
        className=Cn.(
          "absolute top-0 left-0 w-12 h-12  flex items-center justify-center border-r"
          + on("border-green-400 text-green-400", focus)
        )>
        icon
      </span>
      {input(~cn="pl-16", ())}
    </div>
  | None => input()
  };
};
