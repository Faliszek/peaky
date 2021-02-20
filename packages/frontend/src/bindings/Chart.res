type dataLine = {
  x: float,
  y: float,
}

module XYPlot = {
  @module("react-vis") @react.component
  external make: (~children: React.element, ~width: float, ~height: float) => React.element =
    "XYPlot"
}

module LineSeries = {
  type strokeLine = [#solid]

  type curve = [#curveMonotoneX]
  @module("react-vis") @react.component
  external make: (
    ~data: array<dataLine>,
    ~opacity: float,
    ~strokeStyle: strokeLine,
    ~curve: curve,
    ~style: ReactDOM.Style.t=?,
  ) => React.element = "LineSeries"
}

module XAxis = {
  @module("react-vis") @react.component
  external make: (
    ~attr: string,
    ~attrAxis: string,
    ~orientation: string,
    ~tickFormat: 'a => string,
    ~tickTotal: int,
  ) => React.element = "XAxis"
}

module YAxis = {
  @module("react-vis") @react.component
  external make: (~attr: string, ~attrAxis: string, ~orientation: string) => React.element = "YAxis"
}

module DiscreteColorLegend = {
  type t = {
    title: string,
    color: string,
  }

  @module("react-vis") @react.component
  external make: (
    ~items: array<React.element>,
    ~orientation: string=?,
    ~style: ReactDOM.Style.t=?,
  ) => React.element = "DiscreteColorLegend"
}

module HorizontalGridLines = {
  @module("react-vis") @react.component
  external make: (~style: ReactDOM.Style.t) => React.element = "HorizontalGridLines"
}
