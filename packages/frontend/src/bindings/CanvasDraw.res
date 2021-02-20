// type data;
// type t = {getSaveData: unit => string};
// let dataToString = x => Obj.magic(Js.Json.stringifyAny(x));
// [@bs.module "react-canvas-draw"] [@react.component]
// external make:
//   (
//     ~ref: ReactDOM.domRef=?,
//     ~onChange: t => unit=?,
//     ~loadTimeOffset: float=?,
//     ~lazyRadius: float=?,
//     ~brushRadius: float=?,
//     ~brushColor: string=?,
//     ~catenaryColor: string=?,
//     ~gridColor: string=?,
//     ~hideGrid: bool=?,
//     ~canvasWidth: float=?,
//     ~canvasHeight: float=?,
//     ~disabled: bool=?,
//     ~imgSrc: string=?,
//     ~backgroundColor: string=?,
//     // ~saveData: null,
//     ~saveData: string=?,
//     ~immediateLoading: bool=?,
//     ~hideInterface: bool=?,
//     ~style: ReactDOM.Style.t=?
//   ) =>
//   React.element =
//   "default";

@module("react-sketch-canvas") @react.component
external make: (
  ~width: string=?,
  ~height: string=?,
  ~background: string=?,
  ~strokeColor: string=?,
  ~onUpdate: 'a,
  ~ref: 'b,
  ~withTimestamp: bool=?,
  ~style: ReactDOM.Style.t=?,
) => React.element = "ReactSketchCanvas"
