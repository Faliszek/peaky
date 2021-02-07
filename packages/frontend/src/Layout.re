module Menu = {
  module Item = {
    [@react.component]
    let make = (~icon, ~text, ~active=false, ~view) => {
      let className =
        active
          ? "bg-green-500 text-white  hover:text-white"
          : "text-green-600 bg-white  hover:text-green-500";
      <li className="bg-white mb-1" onClick={_ => Router.(push(view))}>
        <a
          className=Cn.(
            "px-4 py-2 flex items-center font-medium transition-colors rounded-r-lg"
            + className
          )>
          icon
          <Text> text </Text>
        </a>
      </li>;
    };
  };

  [@react.component]
  let make = (~firstName, ~lastName) => {
    let url = ReasonReactRouter.useUrl();

    <nav
      className="w-40  h-screen  bg-white border-r-2 border-gray-100 z-10 pr-1 flex flex-col justify-between fixed left-0 top-0">
      <div>
        <div className="flex justify-start ml-4">
          <div className="h-24 flex items-center justify-center mb-4">
            <span className=" bg-green-500 p-3 rounded-full shadow-lg mr-2">
              <Icons.Activity size="18" color="white" />
            </span>
            <span className="text-green-500 uppercase font-bold text-md">
              <Text> {j|Peaky|j} </Text>
            </span>
          </div>
        </div>
        <ul className="bg-white">
          <Item
            icon={<Icons.Calendar className="mr-3" size="14" />}
            text={j|Kalendarz|j}
            view=Router.Calendar
            active={Router.Calendar == url.path->Router.toView}
          />
          <Item
            icon={<Icons.User className="mr-3" size="14" />}
            text={j|Pacjenci|j}
            view=Router.Patients
            active={
              switch (url.path) {
              | ["patients", _, _] => true
              | ["patients", _] => true
              | ["patients"] => true
              | _ => false
              }
            }
          />
          <Item
            icon={<Icons.List className="mr-3" size="14" />}
            text={j|Historia|j}
            view=Router.Visits
            active={Router.Visits == url.path->Router.toView}
          />
          <Item
            icon={<Icons.Share className="mr-3" size="14" />}
            text={j|Konsultacje|j}
            view=Router.Consultations
            active={
              switch (url.path) {
              | ["consultations", _, _] => true
              | ["consultations", _] => true
              | ["consultations"] => true
              | _ => false
              }
            }
          />
        </ul>
      </div>
      // <Item
      //   icon={<Icons.Settings className="mr-3" size="14" />}
      //   text={j|Ustawienia|j}
      //   view=Router.Settings
      //   active={Router.Settings == url.path->Router.toView}
      // />
      <div className="flex px-2 py-4 items-center justify-center flex-col">
        <Avatar firstName lastName />
        <div className="h-4" />
        <Button
          icon={<Icons.ArrowRight size="18" />} onClick={_ => Auth.signOut()}>
          <Text> {j|Wyloguj się|j} </Text>
        </Button>
      </div>
    </nav>;
  };
};

module Query = [%graphql
  {|
  query IncomingsConsultations {
    me {
      id
      firstName
      lastName
    }
    consultations {
      id
      userIds
      callerId
    }


  }
|}
];

module Decline = [%graphql
  {|
  mutation Decline($id: String!, $callerId: String!, $userIds: [String!]!) {
    decline(id:$id, callerId:$callerId, userIds: $userIds) {
      id
    }



  }
|}
];

[@react.component]
let make = (~children) => {
  let consultations = Query.use(~pollInterval=2000, ());
  let (decline, declineResult) =
    Decline.use(~refetchQueries=[|Query.refetchQueryDescription()|], ());
  let (incomingCall, setIncomingCall) = React.useState(_ => None);
  let url = ReasonReactRouter.useUrl();

  React.useEffect1(
    () => {
      {
        switch (consultations) {
        | {data: Some({me, consultations})} =>
          let incoming =
            consultations
            ->Array.keep(c =>
                c.userIds->Js.Array2.find(x => x == me.id)->Option.isSome
              )
            ->Array.get(0);

          setIncomingCall(_ => incoming);
        | _ => ()
        };
      };

      None;
    },
    [|consultations|],
  );

  let myId =
    consultations.data->Option.map(c => c.me.id)->Option.getWithDefault("");
  let firstName =
    consultations.data
    ->Option.map(c => c.me.firstName)
    ->Option.getWithDefault("");
  let lastName =
    consultations.data
    ->Option.map(c => c.me.lastName)
    ->Option.getWithDefault("");

  <div className="flex">
    <Menu lastName firstName />
    <div className="bg-white flex-1 pl-40"> children </div>
    {switch (incomingCall, url.path) {
     | (Some(call), path) when path->List.get(1) != Some(call.id) =>
       <div>
         {declineResult.loading ? <Loader /> : React.null}
         <div
           className="fixed bottom-12 right-12 flex p-8 shadow-lg border border-gray flex-col bg-white rounded-xl">
           <span className="text-3xl text-gray-500 mb-8">
             <Text> {j|Przychodzące połączenie|j} </Text>
           </span>
           <div className="flex justify-around gap-8">
             <div
               className=" animate-pulse flex justify-center flex-col items-center w-24 h-24 rounded-full bg-green-500 hover:bg-green-400 cursor-pointer text-white "
               onClick={_ => Router.(push(ConsultationRoom(call.id)))}>
               <Icons.Phone size="24" />
               <Text> {j|Odbierz|j} </Text>
             </div>
             <div
               className="flex justify-center flex-col items-center w-24 h-24 rounded-full bg-red-500 hover:bg-red-400 cursor-pointer text-white "
               onClick={_ =>
                 decline({
                   id: call.id,
                   callerId: call.callerId,
                   userIds: call.userIds->Array.keep(x => x != myId),
                 })
                 ->Request.onFinish(
                     ~onOk=_ => setIncomingCall(_ => None),
                     ~onError=_ => (),
                   )
               }>
               <Icons.PhoneOff />
               <Text> {j|Odrzuć|j} </Text>
             </div>
           </div>
         </div>
       </div>
     | _ => React.null
     }}
  </div>;
};
