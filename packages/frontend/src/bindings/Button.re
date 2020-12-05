[@react.component]
let make = (~children, ~icon=?, ~onClick=?) =>
  <button
    ?onClick
    className=" px-4 py-2 border-green-500 text-green-500 font-medium rounded-lg transition-colors hover:text-white hover hover:bg-green-500 flex items-center">
    <span className=Cn.(icon->mapSome(_ => "mr-2"))> children </span>
    {icon->Option.getWithDefault(React.null)}
  </button>;

module CTA = {
  [@react.component]
  let make = (~htmlType=?, ~loading=false, ~children) => {
    <button
      type_=?htmlType
      className="relative px-8 h-12  shadow-lg flex items-center justify-center bg-green-400  text-white text-xl rounded-3xl focus:outline-none transition-colors hover:bg-green-300 overflow-hidden">
      children
      <span
        className=Cn.(
          "w-full h-full flex items-center justify-center  transition-opacity absolute top-0 left-0 bg-green-50  rounded-3xl"
          + (loading ? "opacity-100" : "opacity-0")
        )>
        <Icons.Spinner className="animate-spin-fast text-green-400" />
      </span>
    </button>;
  };
};
