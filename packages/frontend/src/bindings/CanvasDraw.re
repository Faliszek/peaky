type data;
type t = {getSaveData: unit => string};

let dataToString = x => Obj.magic(Js.Json.stringifyAny(x));

[@bs.module "react-canvas-draw"] [@react.component]
external make:
  (
    ~onChange: t => unit=?,
    ~loadTimeOffset: float=?,
    ~lazyRadius: float=?,
    ~brushRadius: float=?,
    ~brushColor: string=?,
    ~catenaryColor: string=?,
    ~gridColor: string=?,
    ~hideGrid: bool=?,
    ~canvasWidth: float=?,
    ~canvasHeight: float=?,
    ~disabled: bool=?,
    ~imgSrc: string=?,
    ~backgroundColor: string=?,
    // ~saveData: null,
    ~saveData: string=?,
    ~immediateLoading: bool=?,
    ~hideInterface: bool=?,
    ~style: ReactDOM.Style.t=?
  ) =>
  React.element =
  "default";
