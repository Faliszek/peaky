open Calls_Query.Query;

type userCallFrom = Frontend.Calls_Query.Query.Query_inner.t_calls_from_;
type userCallTo = Frontend.Calls_Query.Query.Query_inner.t_calls_to_;

let withWho = (from_: userCallFrom, to_: userCallTo, myId) => {
  Js.log2(from_, to_);
  switch (from_, to_, myId) {
  | (from_, _, myId) when from_.id != myId =>
    Some(from_.firstName ++ " " ++ from_.lastName)

  | (_, to_, myId) when to_.id != myId =>
    Some(to_.firstName ++ " " ++ to_.lastName)
  | _ => None
  };
};

[@react.component]
let make = (~callMode=false) => {
  let (executeQuery, queryCalls) = Calls_Query.Query.useLazy();

  React.useEffect0(() => {
    executeQuery();
    None;
  });

  <Page
    title="Wizyty"
    actions={
      <Button.CTA onClick={_ => executeQuery()}>
        <Text> {|Odśwież listę|} </Text>
      </Button.CTA>
    }>
    {switch (queryCalls) {
     | Executed({loading: true}) => <Spinner />
     | Executed({data: Some({calls, me})}) =>
       let calls =
         calls->Array.map(c =>
           Call.fromGraphql(
             ~duration=c.duration,
             ~id=c.id,
             ~answered=c.answered,
             ~timestamp=c.timestamp,
             ~withWho=?withWho(c.from_, c.to_, me.id),
             (),
           )
         );

       <Visits_History calls callMode />;
     | _ => React.null
     }}
  </Page>;
};
