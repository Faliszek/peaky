module SearchComponent = {
  [@react.component]
  let make = (~children) => <div className="flex-1 mr-8"> children </div>;
};

module Query = [%graphql
  {|
  query Search($specialization: String!, $firstName: String!, $lastName: String!) {
    me {
      id
    }
    searchSpecialist(specialization: $specialization, firstName:$firstName, lastName: $lastName) {
      id
      firstName
      lastName
      specialization
      online
      # avatar
    }
  }
|}
];

module CreateConsultation = [%graphql
  {|
  mutation Consultation($userIds: [String!]!, $callerId: String!) {
    createConsultation(userIds: $userIds, callerId: $callerId){
      id
      callerId
      userIds
    }
  }
|}
];

module Checkbox = {
  [@react.component]
  let make = (~checked, ~onChange, ~disabled) => {
    let bg = checked ? "bg-green-500" : "bg-white border-2 border-gray-400";
    let state = disabled ? "" : "cursor-pointer";
    <div
      className=Cn.(
        "w-8 h-8 rounded-xl flex items-center justify-center text-white"
        + bg
        + state
      )
      onClick={_ => !disabled ? onChange() : ()}>
      {checked ? <Icons.Check /> : React.null}
    </div>;
  };
};
[@react.component]
let make = () => {
  let specialization = Select.use();
  let (firstName, setFirstName) = React.useState(_ => "");
  let (lastName, setLastName) = React.useState(_ => "");

  let (executeQuery, result) = Query.useLazy();

  let (checkedIds, setCheckedIds) = React.useState(_ => [||]);

  let ids = checkedIds->Array.size->Js.Int.toString;

  let (createConsultation, createConsultationResult) =
    CreateConsultation.use();

  <Page title="Konsultacje">
    <div
      className="text-lg p-4 flex items-center border-2 border-blue-100 rounded-lg mb-12 bg-blue-50 text-blue-300">
      <Icons.Info />
      <span className="ml-4 ">
        <Text>
          {j|Tutaj możesz znaleźć specjalistów z różnych dziedzin którzy mogą pomóc ci w diagnozie twoich pacjentów|j}
        </Text>
      </span>
    </div>
    <div className="flex justify-items-start">
      <SearchComponent>
        <Select
          placeholder={j|Wybierz specjalizację|j}
          value={specialization.value}
          search={specialization.search}
          visible={specialization.visible}
          onVisibleChange={specialization.setVisible}
          onChange={specialization.setValue}
          onSearchChange={specialization.setSearch}
          options=Specialization.all
          icon={<Icons.Tag />}
        />
      </SearchComponent>
      <SearchComponent>
        <Input
          value=firstName
          onChange={v => setFirstName(_ => v)}
          placeholder={j|Imię|j}
        />
      </SearchComponent>
      <SearchComponent>
        <Input
          value=lastName
          onChange={v => setLastName(_ => v)}
          placeholder={j|Nazwisko|j}
        />
      </SearchComponent>
      <Button.CTA
        icon={<Icons.Search />}
        onClick={_ => {
          executeQuery({
            firstName,
            lastName,
            specialization: specialization.search,
          })
        }}>
        <span className="ml-4"> <Text> {j|Wyszukaj|j} </Text> </span>
      </Button.CTA>
    </div>
    <div className="pt-12">
      {switch (result) {
       | Unexecuted(_) =>
         <NoData
           icon={<Icons.Search size="64" />}
           title={j|Wyszukaj specjalistów|j}
           text={j|Wprowadź kryteria wyszukiwania a następnie kliknij przycisk "Wyszukaj"|j}
         />
       | Executed({loading: true}) => <Spinner />
       | Executed({data: Some({searchSpecialist, me})}) =>
         <div>
           <div className="shadow-md border border-gray-200 rounded-lg px-8">
             <div className="flex w-full">
               <Table.Th text={j||j} width="w-1/5" />
               <Table.Th text={j|Użytkownik|j} width="w-1/4" />
               <Table.Th text={j|Specjalizacja|j} width="w-1/4" />
             </div>
             //  <Table.Th text={j||j} width="w-1/2" />
             <div className="flex w-full flex-col">
               {searchSpecialist
                ->Array.map(c => {
                    <div
                      key={c.id}
                      className="flex w-full border-t border-gray-300 items-center jus">
                      <Table.Td width="w-1/5">
                        <Checkbox
                          disabled={!c.online}
                          checked={
                            checkedIds
                            ->Js.Array2.find(x => x == c.id)
                            ->Option.isSome
                          }
                          onChange={_ =>
                            setCheckedIds(checked =>
                              checked
                              ->Js.Array2.find(x => x == c.id)
                              ->Option.isSome
                                ? checked->Array.keep(x => x != c.id)
                                : checked->Array.concat([|c.id|])
                            )
                          }
                        />
                      </Table.Td>
                      <Table.Td width="w-1/4">
                        <div
                          className="flex items-center justify-start w-full">
                          <Avatar
                            firstName={c.firstName}
                            lastName={c.lastName}
                          />
                          <span className="ml-4 text-xl">
                            <Text> {c.firstName ++ " " ++ c.lastName} </Text>
                          </span>
                        </div>
                      </Table.Td>
                      <Table.Td width="w-1/4">
                        <Text> {c.specialization} </Text>
                      </Table.Td>
                    </div>
                  })
                ->React.array}
             </div>
           </div>
           {checkedIds->Array.size != 0
              ? <div className="fixed right-12 bottom-12">
                  <Button.CTA
                    loading={createConsultationResult.loading}
                    className="  animate-pulse"
                    onClick={_ =>
                      createConsultation({
                        userIds: checkedIds,
                        callerId: me.id,
                      })
                      ->Request.onFinish(
                          ~onError=_ => (),
                          ~onOk=
                            ({createConsultation: Some(consultation)}) => {
                              CreateConsultation.(
                                Router.push(
                                  ConsultationRoom(consultation.id),
                                )
                              )
                            },
                        )
                    }
                    icon={<Icons.Video className="mr-4" />}>
                    <Text> {j|Przejdź do konsultacji online ($ids)|j} </Text>
                  </Button.CTA>
                </div>
              : React.null}
         </div>

       | _ => React.null
       }}
    </div>
  </Page>;
};
