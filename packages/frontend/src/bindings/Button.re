[@bs.module "antd"] [@react.component]
external make:
  (
    ~children: React.element,
    ~htmlType: string=?,
    ~_type: [ | `primary | `default | `ghost | `dashed | `link | `text]=?,
    ~shape: [ | `cricle | `round]=?,
    ~loading: bool=?,
    ~block: bool=?,
    ~size: [ | `large | `middle | `small]=?,
    ~className: string=?
  ) =>
  React.element =
  "Button";
