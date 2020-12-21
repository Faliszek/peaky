module SearchComponent = {
  [@react.component]
  let make = (~children) => <div className="flex-1 mr-8"> children </div>;
};

[@react.component]
let make = () => {
  let specialization = Select.use();

  let (firstName, setFirstName) = React.useState(_ => "");
  let (lastName, setLastName) = React.useState(_ => "");

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
      <Button.CTA icon={<Icons.Search />}>
        <span className="ml-4"> <Text> {j|Wyszukaj|j} </Text> </span>
      </Button.CTA>
    </div>
  </Page>;
};
