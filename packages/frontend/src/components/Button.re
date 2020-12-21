[@react.component]
let make = (~children, ~icon=?, ~onClick=?) =>
  <button
    ?onClick
    className=" px-4 py-2 border-green-500 text-green-500 font-medium rounded-md transition-colors hover:text-white hover hover:bg-green-500 flex items-center">
    <span className=Cn.(icon->mapSome(_ => "mr-2"))> children </span>
    {icon->Option.getWithDefault(React.null)}
  </button>;

module Row = {
  [@react.component]
  let make = (~children) => {
    <div className="flex justify-center "> children </div>;
  };
};
module SmallRound = {
  [@react.component]
  let make = (~icon, ~onClick=?) => {
    <button
      ?onClick
      className="rounded-full bg-green-500 w-12 h-12 flex items-center justify-center shadow-md text-white cursor-pointer transition-colors hover:bg-green-400 focus:outline-none">
      icon
    </button>;
  };
};

module Nav = {
  [@react.component]
  let make = (~onClick, ~children, ~className=?) =>
    <div
      onClick
      className=Cn.(
        "p-2 cursor-pointer rounded-lg bg-white transition-colors hover:bg-gray-100"
        + mapSome(className, x => x)
      )>
      children
    </div>;
};

module CTA = {
  [@react.component]
  let make =
      (
        ~htmlType=?,
        ~loading=false,
        ~children,
        ~className=?,
        ~icon=?,
        ~type_=`primary,
        ~onClick=?,
      ) => {
    let colors =
      switch (type_) {
      | `primary => "border border-green-400 bg-green-400  text-white hover:bg-green-300 hover:border-green-300"
      | `ghost => "border border-green-400 bg-white  text-green-400 hover:text-green-300 hover:border-green-300"
      };

    <button
      ?onClick
      type_=?htmlType
      className=Cn.(
        "relative px-8 h-12  shadow-lg flex items-center justify-center text-lg rounded-3xl focus:outline-none transition-colors  overflow-hidden"
        + colors
        + Cn.mapSome(className, x => x)
      )>
      {icon->Option.getWithDefault(React.null)}
      children
      <span
        className=Cn.(
          "w-full h-full flex items-center justify-center  transition-opacity absolute top-0 left-0 bg-green-50  rounded-3xl ring-green-800 focus:ring-2"
          + (loading ? "opacity-100" : "opacity-0")
        )>
        <Icons.Spinner className="animate-spin text-green-400" />
      </span>
    </button>;
  };
};
