open Visit;

[@react.component]
let make = (~calls, ~name=?) => {
  // let queryPatients = Patient_List_Query.Query.use();
  //TODO: api for calls
  <div className="shadow-md border border-gray-200 rounded-lg px-8">
    <div className="flex w-full ">
      <div
        className="w-1/6 px-4 py-6 text-lg font-bold text-gray-600 text-center">
        <Text> {j|Numer ID|j} </Text>
      </div>
      <div
        className="w-1/5 px-4 py-6 text-lg font-bold text-gray-600 text-center">
        <Text> {j|Czas trwania|j} </Text>
      </div>
      <div
        className="w-1/5 px-4 py-6 text-lg font-bold text-gray-600 text-center">
        <Text> {j|Data rozpoczęcia|j} </Text>
      </div>
      <div
        className="w-1/5 px-4 py-6 text-lg font-bold text-gray-600 text-center">
        <Text> {j|Pacjent|j} </Text>
      </div>
      <div
        className="w-1/3 px-4 py-6 text-lg font-bold text-gray-600 text-center">
        <Text> {j|Szczegóły|j} </Text>
      </div>
    </div>
    <div className="flex w-full flex-col">
      {calls
       ->Array.map(c => {
           let iconColor = c.answered ? "text-green-500" : "text-red-500";

           <div className="flex w-full border-t border-gray-300 items-center">
             <div
               className="w-1/6 px-4 py-4 text-center text-lg flex items-center justify-center">
               <Text> {c.id} </Text>
               <span className=Cn.("ml-2" + iconColor)>
                 {c.answered ? <Icons.PhoneCall /> : <Icons.PhoneMissed />}
               </span>
             </div>
             <div className="w-1/5 px-4 py-4 text-center text-lg ">
               <Text>
                 {(c.duration +. Time.now()->Time.startOfDay->Time.getTime)
                  ->Js.Date.fromFloat
                  ->Time.format("HH:mm")}
               </Text>
             </div>
             <div className="w-1/5 px-4 py-4 text-center text-lg ">
               <Text>
                 {c.timestamp
                  ->float_of_string
                  ->Js.Date.fromFloat
                  ->Time.format("dd.MM.yyyy, HH:mm")}
               </Text>
             </div>
             <div className="w-1/5 px-4 py-4 text-center text-lg ">
               {switch (name) {
                | Some(name) => <Text> name </Text>
                | None => "-"->React.string
                }}
             </div>
             <div
               className="w-1/3 px-4 py-6 text-lg font-bold text-gray-600 text-center flex justify-center">
               <Button.CTA icon={<Icons.List className="mr-4" />}>
                 <Text> {j|Zobacz Szczegóły|j} </Text>
               </Button.CTA>
             </div>
           </div>;
         })
       ->React.array}
    </div>
  </div>;
};
