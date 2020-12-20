[@react.component]
let make = (~checked, ~onChange, ~loading=false) => {
  let bg = checked ? "bg-green-400" : "bg-gray-200";
  let border = checked ? "border-green-400" : "border-gray-200";

  <div onClick={_ => onChange(!checked)}>
    <label className="flex items-center cursor-pointer" htmlFor="toggleA">
      <div className="relative">
        <input
          id="toogleA"
          type_="checkbox"
          className="hidden"
          checked
          onChange=Js.log
        />
        <div
          className=Cn.(
            "w-12 h-6 rounded-full shadow-inner transition-all" + bg
          )
        />
        <div
          className=Cn.(
            "absolute w-6 h-6 bg-white rounded-full shadow-sm inset-y-0 left-0 transition-all border-2 transform flex items-center justify-center"
            + border
            + on("translate-x-full", checked)
          )>
          {loading
             ? <Icons.Spinner
                 size="16"
                 className="animate-spin text-gray-400 "
               />
             : React.null}
        </div>
      </div>
      <div className="ml-3 text-gray-700 font-medium" />
    </label>
  </div>;
};
