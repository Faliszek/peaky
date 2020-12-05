module Block = {
  [@react.component]
  let make = (~children) => {
    <div className="shadow-sm p-8"> children </div>;
  };
};

[@react.component]
let make = (~title, ~children, ~hasBackButton=false) => {
  <div className="px-8 py-8  min-h-full">
    <div className="p-4 bg-white rounded-lg ">
      <div className="flex items-center text-2xl text-gray-700 mb-4">
        {hasBackButton
           ? <div
               onClick={_ => Router.goBack()}
               className="mr-4 p-2 cursor-pointer rounded-lg bg-white transition-colors hover:bg-gray-100">
               <Icons.ArrowLeft />
             </div>
           : React.null}
        title->React.string
      </div>
      <div className="text-gray-600"> children </div>
    </div>
  </div>;
};
