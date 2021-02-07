let useConsultation: unit => unit = [%bs.raw
  {|
function() {
    console.log("done")
}
|}
];
[@react.component]
let make = (~id) => {
  useConsultation();
  <div> "Test"->React.string </div>;
};
