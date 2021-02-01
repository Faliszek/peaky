module Th = {
  [@react.component]
  let make = (~text, ~width) => {
    <div
      className=Cn.(
        "px-4 py-6 text-lg font-bold text-gray-600 text-center" + width
      )>
      <Text> text </Text>
    </div>;
  };
};

module Td = {
  [@react.component]
  let make = (~width, ~children) => {
    <div
      className=Cn.(
        "px-4 py-4 text-center text-lg flex items-center justify-center"
        + width
      )>
      children
    </div>;
  };
};
