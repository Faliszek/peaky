[@react.component]
let make = (~avatar=?, ~firstName=?, ~lastName=?, ~size=`default) => {
  let fontSize =
    switch (size) {
    | `default => "text-3xl"
    | `big => "text-6xl"
    };
  let size =
    switch (size) {
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
      )>
      <span className=Cn.("text-white" + fontSize)>
        {(firstName->Js.String.get(0) ++ lastName->Js.String.get(0))
         ->React.string}
      </span>
    </div>
  | _ => React.null
  };
};
