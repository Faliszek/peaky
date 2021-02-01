module SearchComponent = {
  [@react.component]
  let make = (~children) => <div className="flex-1 mr-8"> children </div>;
};

module Query = [%graphql
  {|
  query Search($specialization: String!, $firstName: String!, $lastName: String!) {
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

[@react.component]
let make = () => {
  let specialization = Select.use();
  let (firstName, setFirstName) = React.useState(_ => "");
  let (lastName, setLastName) = React.useState(_ => "");

  let (executeQuery, result) = Query.useLazy();

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
       | Executed({data: Some({searchSpecialist})}) =>
         <div className="shadow-md border border-gray-200 rounded-lg px-8">
           <div className="flex w-full">
             <Table.Th text={j|Użytkownik|j} width="w-1/4" />
             <Table.Th text={j|Specjalizacja|j} width="w-1/4" />
             <Table.Th text={j||j} width="w-1/2" />
           </div>
           <div className="flex w-full flex-col">
             {searchSpecialist
              ->Array.map(c => {
                  <div
                    key={c.id}
                    className="flex w-full border-t border-gray-300 items-center jus">
                    <Table.Td width="w-1/4">
                      <div className="flex items-center justify-start w-full">
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
                    <Table.Td width="w-1/2">
                      <Button.CTA
                        icon={
                          c.online
                            ? <Icons.Video className="mr-4" />
                            : <Icons.PhoneMissed className="mr-4" />
                        }
                        disabled={!c.online}>
                        <Text>
                          {c.online
                             ? {j|Przejdź do konsultacji online|j}
                             : {j|Użytkownik jest niedostępny|j}}
                        </Text>
                      </Button.CTA>
                    </Table.Td>
                  </div>
                })
              ->React.array}
           </div>
         </div>

       | _ => React.null
       }}
    </div>
  </Page>;
};
