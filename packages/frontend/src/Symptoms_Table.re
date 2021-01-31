open Symptoms;

module SymptomRow = {
  module Label = {
    [@react.component]
    let make = (~label, ~value) => {
      <div className="px-2 py-3 text-gray-500 flex border border-gray-50">
        <div className="flex-1 text-md">
          <Text> label </Text>
          <Text> " : " </Text>
        </div>
        <div className="flex-1">
          <Text> {value == "" ? "-" : value} </Text>
        </div>
      </div>;
    };
  };
  [@react.component]
  let make =
      (
        ~name,
        ~index,
        ~circumstances,
        ~occurences,
        ~description,
        ~causedBy,
        ~notes,
        ~date,
      ) => {
    let (expanded, setExpanded) = React.useState(_ => true);

    let rotated = expanded ? "rotate-180" : "rotate-0";
    let toggled = !expanded ? "scale-y-0 max-h-0" : "scale-y-100 max-h-full";
    let index = (index + 1)->Js.Int.toString ++ ") ";
    <li className="px-4 py-5 mb-4 rounded-lg border-gray-200 border text-xl">
      <div
        className="flex justify-between cursor-pointer"
        onClick={_ => setExpanded(v => !v)}>
        <span className="text-2xl text-gray-500">
          <Text> {index ++ name} </Text>
        </span>
        <Icons.ChevronDown
          size="36"
          className=Cn.("transition transition-transform transform" + rotated)
        />
      </div>
      <div
        className=Cn.(
          "h-full transition transition-transform transform origin-top rounded-md overflow-hidden mx-6"
          + toggled
        )>
        <div className="h-6" />
        <Label label={j|Okoliczności pojawienia się|j} value=circumstances />
        <Label label={j|Data pierwszego wystąpienia|j} value=date />
        <Label label={j|Częstotliwość występowania|j} value=occurences />
        <Label label={j|Opis|j} value=description />
        <Label label={j|Spowodowany przez|j} value=causedBy />
        <Label label={j|Dodatkowe informacje|j} value=notes />
      </div>
    </li>;
  };
};

[@react.component]
let make = (~symptoms) => {
  <ol>

      {symptoms
       ->Array.mapWithIndex((index, s) => {
           <SymptomRow
             key={s.id}
             name={s.name}
             index
             circumstances={s.circumstances}
             occurences={s.occurences}
             description={s.description}
             causedBy={s.causedBy}
             notes={s.notes}
             date={s.date}
           />
         })
       ->React.array}
    </ol>;
    //   <div className="shadow-md border border-gray-200 rounded-lg px-8">
    //     <div className="flex w-full ">
    //       <div
    //         className="w-1/6 px-4 py-6 text-lg font-bold text-gray-600 text-center">
    //         <Text> {j|Numer ID|j} </Text>
    //       </div>
    //       <div
    //         className="w-1/5 px-4 py-6 text-lg font-bold text-gray-600 text-center">
    //         <Text> {j|Czas trwania|j} </Text>
    //       </div>
    //       <div
    //         className="w-1/5 px-4 py-6 text-lg font-bold text-gray-600 text-center">
    //         <Text> {j|Data rozpoczęcia|j} </Text>
    //       </div>
    //       <div
    //         className="w-1/5 px-4 py-6 text-lg font-bold text-gray-600 text-center">
    //         <Text> {j|Pacjent|j} </Text>
    //       </div>
    //       <div
    //         className="w-1/3 px-4 py-6 text-lg font-bold text-gray-600 text-center">
    //         <Text> {j|Szczegóły|j} </Text>
    //       </div>
    //     </div>
    //     <div className="flex w-full flex-col">
    //       {calls
    //        ->Array.map(c => {
    //            let iconColor = c.answered ? "text-green-500" : "text-red-500";
    //            <div className="flex w-full border-t border-gray-300 items-center">
    //              <div
    //                className="w-1/6 px-4 py-4 text-center text-lg flex items-center justify-center">
    //                <Text> {c.id} </Text>
    //                <span className=Cn.("ml-2" + iconColor)>
    //                  {c.answered ? <Icons.PhoneCall /> : <Icons.PhoneMissed />}
    //                </span>
    //              </div>
    //              <div className="w-1/5 px-4 py-4 text-center text-lg ">
    //                <Text>
    //                  {(c.duration +. Time.now()->Time.startOfDay->Time.getTime)
    //                   ->Js.Date.fromFloat
    //                   ->Time.format("HH:mm")}
    //                </Text>
    //              </div>
    //              <div className="w-1/5 px-4 py-4 text-center text-lg ">
    //                <Text>
    //                  {c.timestamp
    //                   ->float_of_string
    //                   ->Js.Date.fromFloat
    //                   ->Time.format("dd.MM.yyyy, HH:mm")}
    //                </Text>
    //              </div>
    //              <div className="w-1/5 px-4 py-4 text-center text-lg ">
    //                {switch (name) {
    //                 | Some(name) => <Text> name </Text>
    //                 | None => "-"->React.string
    //                 }}
    //              </div>
    //              <div
    //                className="w-1/3 px-4 py-6 text-lg font-bold text-gray-600 text-center flex justify-center">
    //                <Button.CTA icon={<Icons.List className="mr-4" />}>
    //                  <Text> {j|Zobacz Szczegóły|j} </Text>
    //                </Button.CTA>
    //              </div>
    //            </div>;
    //          })
    //        ->React.array}
    //     </div>
    //   </div>;
};
