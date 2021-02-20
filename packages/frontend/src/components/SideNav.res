@react.component
let make = (~visible, ~onClose, ~title, ~children) =>
  <div
    className={
      open Cn
      "fixed right-0 top-0 z-40 h-screen w-96 p-8 shadow-xl bg-white transform transition-transform" +
      on("translate-x-96", !visible)
    }>
    <div className="mb-8 flex items-center ">
      <Button.Nav onClick={_ => onClose()}> <Icons.ArrowLeft /> </Button.Nav>
      <span className="text-xl block ml-4 "> <Text> title </Text> </span>
    </div>
    children
  </div>
