[@bs.module "antd"] [@react.component]
external make:
  (
    ~value: string,
    ~onChange: ReactEvent.Form.t => unit,
    ~placeholder: string=?,
    ~className: string=?,
    ~_type: string=?,
    ~autocomplete: string=?
  ) =>
  React.element =
  "Input";
