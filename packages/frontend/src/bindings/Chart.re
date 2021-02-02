type dataLine = {
  x: float,
  y: float,
};

module XYPlot = {
  [@bs.module "react-vis"] [@react.component]
  external make:
    (~children: React.element, ~width: float, ~height: float) => React.element =
    "XYPlot";
};

module LineSeries = {
  type strokeLine = [ | `solid];

  type curve = [ | `curveMonotoneX];
  [@bs.module "react-vis"] [@react.component]
  external make:
    (
      ~data: array(dataLine),
      ~opacity: float,
      ~strokeStyle: strokeLine,
      ~curve: curve,
      ~style: ReactDOM.Style.t=?
    ) =>
    React.element =
    "LineSeries";
};

module XAxis = {
  [@bs.module "react-vis"] [@react.component]
  external make:
    (
      ~attr: string,
      ~attrAxis: string,
      ~orientation: string,
      ~tickFormat: 'a => string,
      ~tickTotal: int
    ) =>
    React.element =
    "XAxis";
};

module YAxis = {
  [@bs.module "react-vis"] [@react.component]
  external make:
    (~attr: string, ~attrAxis: string, ~orientation: string) => React.element =
    "YAxis";
};

module DiscreteColorLegendItem = {
  [@bs.module "react-vis"] [@react.component]
  external make:
    (
      ~colors: array(string),
      ~items: array(string),
      ~orientation: string,
      ~style: ReactDOM.Style.t
    ) =>
    React.element =
    "DiscreteColorLegend";
};

module HorizontalGridLines = {
  [@bs.module "react-vis"] [@react.component]
  external make: (~style: ReactDOM.Style.t) => React.element =
    "HorizontalGridLines";
};
