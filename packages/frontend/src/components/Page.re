module Block = {
  [@react.component]
  let make = (~children) => {
    <div className="shadow-sm p-8"> children </div>;
  };
};

[@react.component]
let make = (~title, ~children, ~hasBackButton=false, ~actions=?) => {
  let actionsStyle = actions->Option.isSome ? "flex justify-between" : "";
  <div className="px-8 py-8  min-h-full">
    <div className="px-4 pb-4  bg-white rounded-lg">
      <div className=actionsStyle>
        <div className="flex items-center text-2xl text-gray-700 mb-8">
          {hasBackButton
             ? <Button.Nav onClick={_ => Router.goBack()} className="mr-4">
                 <Icons.ArrowLeft />
               </Button.Nav>
             : React.null}
          title->React.string
        </div>
        {switch (actions) {
         | Some(actions) => <div> actions </div>
         | None => React.null
         }}
      </div>
      <div className="text-gray-600"> children </div>
    </div>
  </div>;
};
