[@react.component]
let make = (~title, ~children) => {
  <div className="px-8 py-8  min-h-full">
    <div className="p-4 bg-white rounded-lg ">
      <div className="text-2xl text-gray-700 mb-4"> title->React.string </div>
      <div className="text-gray-600"> children </div>
    </div>
  </div>;
};
