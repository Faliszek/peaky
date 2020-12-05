module Activity = {
  [@bs.module "react-feather"] [@react.component]
  external make:
    (~color: string=?, ~size: string=?, ~className: string=?) => React.element =
    "Activity";
};

module Calendar = {
  [@bs.module "react-feather"] [@react.component]
  external make:
    (~color: string=?, ~size: string=?, ~className: string=?) => React.element =
    "Calendar";
};

module List = {
  [@bs.module "react-feather"] [@react.component]
  external make:
    (~color: string=?, ~size: string=?, ~className: string=?) => React.element =
    "List";
};

module User = {
  [@bs.module "react-feather"] [@react.component]
  external make:
    (~color: string=?, ~size: string=?, ~className: string=?) => React.element =
    "User";
};

module Share = {
  [@bs.module "react-feather"] [@react.component]
  external make:
    (~color: string=?, ~size: string=?, ~className: string=?) => React.element =
    "Share2";
};

module ArrowRight = {
  [@bs.module "react-feather"] [@react.component]
  external make:
    (~color: string=?, ~size: string=?, ~className: string=?) => React.element =
    "ArrowRight";
};

module Spinner = {
  [@bs.module "react-feather"] [@react.component]
  external make:
    (~color: string=?, ~size: string=?, ~className: string=?) => React.element =
    "Loader";
};
