[@react.component]
let make =
    (
      ~buttonText=?,
      ~buttonIcon=?,
      ~onButtonClick=?,
      ~title,
      ~text,
      ~icon=<Icons.Inbox size="64" />,
    ) => {
  <div className="flex flex-col justify-center items-center py-40 h-full">
    <span className="text-6xl text-gray-400"> icon </span>
    <h1 className="text-gray-400 text-5xl mb-4 my-6"> title->React.string </h1>
    <p className="text-gray-400 text-xl mb-10"> text->React.string </p>
    <div>
      {switch (buttonText, buttonIcon, onButtonClick) {
       | (Some(buttonText), Some(buttonIcon), Some(onButtonClick)) =>
         <Button.CTA icon=buttonIcon onClick=onButtonClick>
           <Text> buttonText </Text>
         </Button.CTA>
       | _ => React.null
       }}
    </div>
  </div>;
};
