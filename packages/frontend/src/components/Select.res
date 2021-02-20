type selectOption<'a> = {
  value: 'a,
  label: string,
}

type clickEvent = {target: Dom.element}
type keyEvent = {key: string}

@scope("window") @val
external onDocumentClick: (string, clickEvent => unit) => unit = "addEventListener"

@bs.send external contains: (Dom.element, Dom.element) => bool = "contains"

@scope("window") @val
external onDocumentClickRemove: (string, clickEvent => unit) => unit = "addEventListener"

let useOutsideClick = (~el: React.ref<'a>, ~visible, onOutsideClick) => React.useEffect2(() => {
    let onOutsideClick = event =>
      switch (el.current->Js.Nullable.toOption, visible) {
      | (Some(el), true) =>
        if !(el->contains(event.target)) {
          onOutsideClick()
        }
      | _ => ()
      }

    onDocumentClick("click", onOutsideClick)

    Some(_ => onDocumentClickRemove("click", onOutsideClick))
  }, (el, visible))

type state<'a> = {
  search: string,
  value: option<selectOption<'a>>,
  visible: bool,
}

type action<'a> =
  | SetVisibility(bool)
  | SetSearch(string)
  | SetValue(option<selectOption<'a>>)

type hook<'a> = {
  search: string,
  value: option<selectOption<'a>>,
  visible: bool,
  setValue: option<selectOption<'a>> => unit,
  setSearch: string => unit,
  setVisible: bool => unit,
}
let initialState = {search: "", value: None, visible: false}

let reducer = (state: state<'a>, action) =>
  switch action {
  | SetVisibility(visible) => {...state, visible: visible}
  | SetSearch(search) => {...state, search: search}
  | SetValue(value) => {...state, value: value}
  }
let use: unit => hook<'a> = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState)

  {
    search: state.search,
    value: state.value,
    visible: state.visible,
    setValue: v => dispatch(SetValue(v)),
    setSearch: v => dispatch(SetSearch(v)),
    setVisible: v => dispatch(SetVisibility(v)),
  }
}

@react.component
let make = (
  ~value: option<selectOption<'a>>,
  ~search,
  ~onSearchChange,
  ~placeholder,
  ~icon,
  ~visible,
  ~onVisibleChange,
  ~options: array<selectOption<'a>>,
  ~onChange,
  ~loading=false,
) => {
  let filterOptions = switch (search, value) {
  | (_, Some(_)) => options
  | ("", _) => options
  | (search, _) => options->Array.keep(o => search->Js.String.includes(o.label))
  }

  let zIndex = 30
  let selectRef = React.useRef(Js.Nullable.null)

  let noOptions = options->Array.length == 0

  let (maxHeight, height) = switch (loading, noOptions, filterOptions) {
  | (true, _, _)
  | (_, true, _) => ("44px", "44px")
  | (_, _, options) =>
    let calc = x => (x * 44 + 20)->Js.Int.toString ++ "px"
    (calc(10), calc(options->Array.length))
  }

  useOutsideClick(~el=selectRef, ~visible, () => onVisibleChange(false))

  <div className="relative" ref={ReactDOM.Ref.domRef(selectRef)}>
    <div
      style={ReactDOM.Style.make(
        ~height,
        ~maxHeight,
        ~top="40px",
        ~paddingTop="10px",
        ~paddingBottom="10px",
        ~zIndex=zIndex->Js.Int.toString,
        (),
      )}
      className={
        open Cn
        "absolute border border-b border-l border-r bg-white rounded-lg w-full overflow-y-scroll transition-transform transform-gpu scale-y-0  origin-top" +
        on("shadow-md  scale-y-100", visible)
      }>
      {switch (loading, noOptions) {
      | (true, _) =>
        <div className="flex items-center justify-center py-2 text-gray-300 text-lg">
          <Icons.Spinner className="animate-spin" />
        </div>
      | (_, true) =>
        <div className="flex items-center justify-center text-gray-300 text-lg">
          <Text> `Brak danych` </Text>
        </div>
      | (_, _) =>
        filterOptions
        ->Array.map(o => {
          let active = Some(o) == value ? "bg-green-500 text-white" : "bg-white"
          <div
            key=o.value
            className={
              open Cn
              "text-lg py-2 px-16 cursor-pointer bg-white hover:bg-gray-100 " + active
            }
            onClick={_ => {
              onChange(Some(o))
              onSearchChange(o.label)
              onVisibleChange(false)
            }}>
            <Text> o.label </Text>
          </div>
        })
        ->React.array
      }}
    </div>
    <Input
      zIndex
      value=search
      onChange={value => {
        onSearchChange(value)
        onChange(None)
      }}
      placeholder
      onFocus={() => onVisibleChange(true)}
      icon
    />
  </div>
}
