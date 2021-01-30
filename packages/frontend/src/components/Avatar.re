[@react.component]
let make = (~avatar=?, ~firstName=?, ~lastName=?, ~size=`default, ~color=?) => {
  let color = color->Option.getWithDefault("green");
  let fontSize =
    switch (size) {
    | `small => "text-sm"
    | `default => "text-3xl"
    | `big => "text-6xl"
    };
  let size =
    switch (size) {
    | `small => "w-8 h-8"
    | `default => "w-24 h-24 "
    | `big => "w-48 h-48"
    };

  switch (avatar, firstName, lastName) {
  | (Some(avatar), _, _) =>
    <img
      src=avatar
      className=Cn.("rounded-full shadow-md border border-gray-100" + size)
    />

  | (_, Some(firstName), Some(lastName)) =>
    <div
      className=Cn.(
        "rounded-full shadow-md border-border-gray flex items-center justify-center bg-green-300"
        + size
      )
      style={ReactDOM.Style.make(
        ~backgroundColor=color,
        ~filter="contrast(200%)",
        (),
      )}>
      <span className=Cn.("text-white" + fontSize)>
        {(firstName->Js.String.get(0) ++ lastName->Js.String.get(0))
         ->React.string}
      </span>
    </div>
  | _ => React.null
  };
};
