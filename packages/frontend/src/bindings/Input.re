module AInput = {
  [@bs.module "antd"] [@react.component]
  external make:
    (
      ~value: string,
      ~onChange: ReactEvent.Form.t => unit,
      ~placeholder: string=?,
      ~className: string=?,
      ~_type: string=?,
      ~autoComplete: string=?
    ) =>
    React.element =
    "Input";
};

[@react.component]
let make =
    (
      ~value,
      ~onChange,
      ~placeholder,
      ~className,
      ~_type="text",
      ~autoComplete="off",
    ) => {
  <AInput
    value
    placeholder
    className
    _type
    autoComplete
    onChange={e => onChange(e->ReactEvent.Form.target##value)}
  />;
};
