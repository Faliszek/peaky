[@react.component]
let make = (~size=`medium, ~className=?, ~color=`green, ~tip=?) => {
  let size =
    switch (size) {
    | `small => "w-5 h-5 p-2"
    | `medium => "w-12 h-12"
    };

  let color =
    switch (color) {
    | `white => "border-white"
    | `green => "border-green-500"
    };

  let spinner =
    <div
      className=Cn.(
        "border-green  border-t-2 animate-spin-fast rounded-full"
        + color
        + size
        + mapSome(className, c => c)
      )
    />;

  switch (tip) {
  | None => spinner
  | Some(tip) =>
    <div className="flex items-center flex-col">
      spinner
      <span className="ml-2 text-gray-700"> tip->React.string </span>
    </div>
  };
};
