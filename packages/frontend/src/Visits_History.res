@react.component
let make = (~calls: array<Call.t>, ~callMode) =>
  <div className="shadow-md border border-gray-200 rounded-lg px-8">
    <div className="flex w-full">
      <Table.Th text=j`Numer ID` width="w-1/6" />
      <Table.Th text=j`Czas trwania` width="w-1/5" />
      <Table.Th text=j`Data rozpoczęcia` width="w-1/5" />
      <Table.Th text=j`Pacjent` width="w-1/5" />
      <Table.Th text=j`Szczegóły` width="w-1/3" />
    </div>
    <div className="flex w-full flex-col">
      {calls
      ->Array.map(c => {
        let iconColor = c.answered ? "text-green-500" : "text-red-500"

        <div className="flex w-full border-t border-gray-300 items-center" key=c.id>
          <Table.Td width="w-1/6 ">
            <Text> c.id </Text>
            <span
              className={
                open Cn
                "ml-2" + iconColor
              }>
              {c.answered ? <Icons.PhoneCall /> : <Icons.PhoneMissed />}
            </span>
          </Table.Td>
          <Table.Td width="w-1/5">
            <Text>
              {(c.duration +. Time.now()->Time.startOfDay->Time.getTime)
              ->Js.Date.fromFloat
              ->Time.format("HH:mm")}
            </Text>
          </Table.Td>
          <Table.Td width="w-1/5">
            <Text> {c.timestamp->Js.Date.fromFloat->Time.format("dd.MM.yyyy, HH:mm")} </Text>
          </Table.Td>
          <Table.Td width="w-1/5">
            {switch (c.withWho, callMode) {
            | (Some(name), false) => <Text> name </Text>
            | _ => "-"->React.string
            }}
          </Table.Td>
          <Table.Td width="w-1/3">
            <Button.CTA icon={<Icons.List className="mr-4" />}>
              <Text> j`Zobacz Szczegóły` </Text>
            </Button.CTA>
          </Table.Td>
        </div>
      })
      ->React.array}
    </div>
  </div>
