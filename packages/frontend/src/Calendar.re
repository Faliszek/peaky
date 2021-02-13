open Time;

let daysInCalendar = 5;
let hours = {"start": 8, "end_": 16};

let makeDays = (~now) => {
  [|
    subDays(now, 2),
    subDays(now, 1),
    now,
    addDays(now, 1),
    addDays(now, 2),
  |];
};

let makeHours = () => {
  Array.range(hours##start, hours##end_);
};

let isToday = date => {
  open Time;
  let today = now()->startOfDay;
  today->getTime == date->getTime;
};

let rowHeight = 60;
let hourWidth = 96;

module Visit = {
  [@react.component]
  let make =
      (
        ~id,
        ~from_,
        ~to_,
        ~patientId,
        ~patients: array(Calendar_Query.Query.t_patients),
        ~days,
      ) => {
    let from_ = from_->float_of_string;
    let to_ = to_->float_of_string;
    let fromDate = from_->Js.Date.fromFloat;
    let toDate = to_->Js.Date.fromFloat;

    let absoluteTop =
      (fromDate->Time.getHours * 60 + fromDate->Time.getMinutes) * 2;
    let topFrom8 = 480 * 2;

    let top = absoluteTop - topFrom8 + rowHeight;

    let leftCellWidth = hourWidth->Js.Int.toString ++ "px";
    let durationAsHeight = Time.differenceInMinutes(to_, from_) * 2;

    let patient = patients->Array.keep(p => p.id == patientId)->Array.get(0);

    let color =
      patient->Option.map(p => p.color)->Option.getWithDefault("blue");

    let first = days->Array.get(0)->Option.map(Js.Date.valueOf);
    let last =
      days
      ->Array.get(4)
      ->Option.map(Time.endOfDay)
      ->Option.map(Js.Date.valueOf);

    let (width, setWidth) = React.useState(() => None);

    let index =
      days
      ->Js.Array2.findIndex(d =>
          d->Time.startOfDay->Js.Date.valueOf
          == fromDate->Time.startOfDay->Js.Date.valueOf
        )
      ->Js.Int.toFloat;

    let visible = width->Option.isSome ? "opacity-100" : "opacity-0";

    let left =
      switch (width) {
      | Some(width) => hourWidth->Js.Int.toFloat +. width *. index
      | None => hourWidth->Js.Int.toFloat
      };

    let userId = Auth.getUserId();
    switch (first, last) {
    | (Some(first), Some(last)) when from_ > first && from_ < last =>
      <div
        ref={ReactDOM.Ref.callbackDomRef(el =>
          el
          ->Js.Nullable.toOption
          ->Option.map(el => {
              setWidth(_ => Some(el->HTMLElement.offsetWidth))
            })
          ->ignore
        )}
        className=Cn.(
          "absolute rounded-lg shadow-md bg-white cursor-pointer border-blue-400 border flex flex-col"
          + visible
        )
        style={ReactDOM.Style.make(
          ~top=top->Js.Int.toString ++ "px",
          ~left=left->Js.Float.toString ++ "px",
          ~width={j|calc( (100% - $leftCellWidth) / 5)|j},
          ~height=durationAsHeight->Js.Int.toString ++ "px",
          ~borderColor=color,
          (),
        )}>
        <div
          className="bg-blue-400 w-full h-8 rounded-t-md flex items-center p-2"
          style={ReactDOM.Style.make(~backgroundColor=color, ())}>
          <span className="text-white font-bold">
            {fromDate->Time.format("HH:mm")->React.string}
            {j| - |j}->React.string
            {toDate->Time.format("HH:mm")->React.string}
          </span>
        </div>
        <div className="flex h-full">
          <div className="flex-2 p-2  h-full">
            {switch (patient) {
             | Some({firstName, lastName, disease, color}) =>
               let name = firstName ++ " " ++ lastName;
               <div className="flex items-center">
                 <Avatar firstName lastName size=`small color />
                 <div className="ml-2 flex flex-col">
                   <span className="text-md"> name->React.string </span>
                   <span className="text-sm text-gray-400">
                     disease->React.string
                   </span>
                 </div>
               </div>;
             | None => React.null
             }}
          </div>
          <div className="flex flex-1 p-2  items-end justify-end h-full">
            <Button.SmallRound
              onClick={_ => Router.(push(Visit(id, userId, patientId)))}
              icon={<Icons.Phone />}
            />
          </div>
        </div>
      </div>
    | _ => React.null
    };
  };
};

[@react.component]
let make = () => {
  let (now, setNow) = React.useState(_ => now()->startOfDay);
  let (visible, setVisible) = React.useState(_ => false);
  let (date, setDate) = React.useState(_ => None);

  let days = makeDays(~now);
  let hours = makeHours();

  let query = Calendar_Query.Query.use();

  let (createVisit, result) =
    Visit_Mutation.Mutation.use(
      ~refetchQueries=[|Calendar_Query.Query.refetchQueryDescription()|],
      (),
    );

  <Page title="Kalendarz">
    <div className="flex items-center justify-center pb-8 text-xl pl-24 ">
      <Button.Nav onClick={_ => setNow(now => now->subDays(5))}>
        <Icons.ChevronLeft size="32" />
      </Button.Nav>
      <span className="select-none mx-4 block">
        {days
         ->Array.get(0)
         ->Option.map(format(_, "dd.MM"))
         ->Option.getWithDefault("")
         ->React.string}
        "  -  "->React.string
        {days
         ->Array.get(days->Array.length - 1)
         ->Option.map(format(_, "dd.MM"))
         ->Option.getWithDefault("")
         ->React.string}
      </span>
      <Button.Nav onClick={_ => setNow(now => now->addDays(5))}>
        <Icons.ChevronRight size="32" />
      </Button.Nav>
    </div>
    <div className="flex border flex-wrap rounded-lg relative ">
      <div
        className="flex w-full bg-gray-50"
        style={ReactDOM.Style.make(
          ~height=rowHeight->Js.Int.toString ++ "px",
          (),
        )}>
        <div className="w-24" />
        {days
         ->Array.map(d =>
             <div
               key={d->format("dd.mm")}
               className=Cn.(
                 "flex-1  text-lg text-center py-4"
                 + on(
                     "text-green-500 font-bold bg-green-100  ring-2 ring-green-300 z-10 rounded-md",
                     isToday(d),
                   )
               )>
               {format(d, "dd.MM")->React.string}
             </div>
           )
         ->React.array}
      </div>
      {hours
       ->Array.map(h =>
           <div key={h->Js.Int.toString} className="flex w-full">
             <div
               className="w-24 border-t"
               style={ReactDOM.Style.make(
                 ~width=hourWidth->Js.Int.toString ++ "px",
                 (),
               )}>
               <div
                 key={h->Js.Int.toString}
                 className="text-center h-32 flex justify-center text-lg"
                 style={ReactDOM.Style.make(
                   ~height=(rowHeight * 2)->Js.Int.toString ++ "px",
                   (),
                 )}>
                 <span className="mt-2">
                   {now->addHours(h)->format("HH:mm")->React.string}
                 </span>
               </div>
             </div>
             {days
              ->Array.map(d => {
                  let date = d->addHours(h);

                  <div
                    key={date->Time.getTime->Js.Float.toString}
                    className="group flex-1 border-l border-t cursor-pointer transition-shadow hover:shadow-inner"
                    onClick={_ => {
                      setVisible(_ => true);
                      setDate(_ => Some(date));
                    }}>
                    <span
                      className="p-4 block text-xl opacity-0 transition-opacity group-hover:opacity-50 ">
                      {date->format("HH:mm")->React.string}
                    </span>
                  </div>;
                })
              ->React.array}
           </div>
         )
       ->React.array}
      {switch (query) {
       | {loading: true} =>
         <div
           className="absolute w-full h-full flex pt-48 justify-center bg-white opacity-80">
           <Spinner tip={|Trwa wczytywanie |} />
         </div>
       | {data: Some(data)} =>
         <div>
           {data.visits
            ->Array.map(v =>
                <Visit
                  key={v.id}
                  id={v.id}
                  from_={v.from_}
                  to_={v.to_}
                  patients={data.patients}
                  patientId={v.patientId}
                  days
                />
              )
            ->React.array}
         </div>
       | _ => React.null
       }}
    </div>
    {switch (query) {
     | {data: Some(data)} =>
       <Calendar_AddVisit
         onClose={_ => setVisible(_ => false)}
         visible
         date
         loading={result.loading}
         patients={data.patients}
         onSubmit={(~patientId, ~from_, ~to_, ~notes) =>
           createVisit({patientId, from_, to_, notes: Some(notes)})
           ->Request.onFinish(
               ~onOk=_ => setVisible(_ => false),
               ~onError=_ => (),
             )
         }
       />
     | _ => React.null
     }}
  </Page>;
};
