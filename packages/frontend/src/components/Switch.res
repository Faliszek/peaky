@react.component
let make = (~checked, ~onChange, ~loading=false) => {
  let bg = switch (checked, loading) {
  | (_, true) => "bg-gray-200"
  | (true, _) => "bg-green-400"
  | _ => "bg-gray-200"
  }

  let border = switch (checked, loading) {
  | (_, true) => "border-gray-200"
  | (true, _) => "border-green-400"
  | _ => "border-gray-200"
  }

  <label className="flex items-center cursor-pointer">
    <div className="relative">
      <input
        type_="checkbox"
        className="hidden"
        checked
        onChange={_ => !loading ? onChange(!checked) : ()}
      />
      <div
        className={
          open Cn
          "w-12 h-6 rounded-full shadow-inner transition-all" + bg
        }
      />
      <div
        className={
          open Cn
          "absolute w-6 h-6 bg-white rounded-full shadow-sm inset-y-0 left-0 transition-all border-2 transform flex items-center justify-center" +
          border +
          on("translate-x-full", checked && !loading)
        }>
        {loading ? <Icons.Spinner size="16" className="animate-spin text-gray-400 " /> : React.null}
      </div>
    </div>
    <div className="ml-3 text-gray-700 font-medium" />
  </label>
}
