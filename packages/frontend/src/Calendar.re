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

[@react.component]
let make = () => {
  let (now, setNow) = React.useState(_ => now()->startOfDay);
  let (visible, setVisible) = React.useState(_ => false);

  let days = makeDays(~now);
  let hours = makeHours();

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
    <div className="flex border flex-wrap rounded-lg ">
      <div className="flex w-full bg-gray-50">
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
           <div className="flex w-full">
             <div className="w-24 border-t">
               <div
                 key={h->Js.Int.toString}
                 className="text-center h-32 flex justify-center text-lg">
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
                    onClick={_ => setVisible(_ => true)}>
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
    </div>
    <Calendar_AddVisit onClose={_ => setVisible(_ => false)} visible />
  </Page>;
};
