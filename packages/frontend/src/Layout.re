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
  let make = () => {
    let url = ReasonReactRouter.useUrl();
    let [@r] asd = "";

    <nav
      className="w-40  h-screen  bg-white border-r-2 border-gray-100 z-10 pr-1 flex flex-col justify-between fixed left-0 top-0">
      <div>

          <div className="flex justify-start ml-4">
            <div className="h-24 flex items-center justify-center mb-4">
              <span className=" bg-green-500 p-3 rounded-full shadow-lg mr-2">
                <Icons.Activity size="18" color="white" />
              </span>
              <span className="text-green-500 uppercase font-bold text-md">
                <Text> {j|Peaky $asd|j} </Text>
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
              active={Router.Consultations == url.path->Router.toView}
            />
          </ul>
        </div>
        // <Item
        //   icon={<Icons.Settings className="mr-3" size="14" />}
        //   text={j|Ustawienia|j}
        //   view=Router.Settings
        //   active={Router.Settings == url.path->Router.toView}
        // />
      <div className="flex px-2 py-4 items-center justify-center">
        <Button
          icon={<Icons.ArrowRight size="18" />} onClick={_ => Auth.signOut()}>
          <Text> {j|Wyloguj się|j} </Text>
        </Button>
      </div>
    </nav>;
  };
};

[@react.component]
let make = (~children) => {
  <div className="flex">
    <Menu />
    <div className="bg-white flex-1 pl-40"> children </div>
  </div>;
};
