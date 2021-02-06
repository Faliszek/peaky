let colors = [|
  "#F87171",
  "#FB923C",
  "#FBBF24",
  "#FACC15",
  "#A3E635",
  "#4ADE80",
  "#34D399",
  "#2DD4BF",
  "#22D3EE",
  "#38BDF8",
  "#60A5FA",
  "#818CF8",
  "#A78BFA",
  "#C084FC",
  "#F5D0FE",
|];

[@react.component]
let make = (~value, ~onChange) => {
  <div className="mb-12 mt-8 flex flex-wrap gap-4">
    {{
       colors->Array.map(c => {
         let active = value == c ? "ring-4 ring-green-400" : "";
         <div
           key=c
           onClick={_ => onChange(c)}
           className=Cn.(
             "w-10 h-10 rounded-md shadow-md border border-gray-100 cursor-pointer"
             + active
           )
           style={ReactDOM.Style.make(~backgroundColor=c, ())}
         />;
       });
     }
     ->React.array}
  </div>;
};
