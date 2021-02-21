module Info = {
  @react.component
  let make = (~name, ~phoneNumber, ~disease, ~lastVisit) =>
    <div className="py-2 px-4 ml-12">
      <div className="text-xl font-medium text-gray-700"> <Text> name </Text> </div>
      <div className="text-lg mb-2 text-gray-600 "> <Text> phoneNumber </Text> </div>
      <div className="text-lg ">
        <span className="text-gray-400"> <Text> `Przypadłość: ` </Text> </span>
        <span className="text-gray-500"> <Text> disease </Text> </span>
      </div>
      <div className="text-lg ">
        <span className="text-gray-400"> <Text> `Ostatnia wizyta: ` </Text> </span>
        <span className="text-gray-500">
          <Text> {lastVisit->Option.getWithDefault("-")} </Text>
        </span>
      </div>
    </div>
}

module Link = {
  @react.component
  let make = () =>
    <div className="text-green-500 flex items-center">
      <Text> `Zobacz więcej` </Text> <Icons.ArrowRight size="16" className="ml-1" />
    </div>
}

@react.component
let make = (~patient, ~className=?) => {
  let {
    id,
    firstName,
    lastName,
    phoneNumber,
    disease,
    lastVisit,
    color,
  }: Patient_List_Query.Query.t_patients = patient
  let name = firstName ++ (" " ++ lastName)
  <div
    onClick={_ => {
      Router.push(Patient(id))
    }}
    className={
      open Cn
      className->mapSome(x => x)
    }>
    <div
      className="m-4 px-4 py-6 flex flex-col w-full h-full shadow-lg rounded-lg cursor-pointer transition-all transform-gpu hover:shadow-lg hover:bg-gray-50">
      <div className="flex flex-1">
        <Avatar firstName lastName color /> <Info name phoneNumber disease lastVisit />
      </div>
      <div className="flex justify-end"> <Link /> </div>
    </div>
    // <div className="absolute top-0 right-0 p-4">
    //   <Button.SmallRound
    //     icon={<Icons.Message />}
    //     onClick={e => {
    //       e
    //       ->ReactEvent.toSyntheticEvent
    //       ->ReactEvent.Synthetic.stopPropagation;
    //       Router.(push(PatientChat(id)));
    //     }}
    //   />
    // </div>
  </div>
}
