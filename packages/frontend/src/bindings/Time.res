let now = () => Js.Date.make()

@module("date-fns")
external addDays: (Js.Date.t, int) => Js.Date.t = "addDays"

@module("date-fns")
external addHours: (Js.Date.t, int) => Js.Date.t = "addHours"

@module("date-fns")
external addMinutes: (Js.Date.t, int) => Js.Date.t = "addMinutes"

@module("date-fns")
external subDays: (Js.Date.t, int) => Js.Date.t = "subDays"

@module("date-fns")
external subHours: (Js.Date.t, int) => Js.Date.t = "subHours"

@module("date-fns")
external format: (Js.Date.t, string) => string = "format"

@module("date-fns") external getTime: Js.Date.t => float = "getTime"

@module("date-fns")
external startOfDay: Js.Date.t => Js.Date.t = "startOfDay"

@module("date-fns") external endOfDay: Js.Date.t => Js.Date.t = "endOfDay"

@module("date-fns")
external differenceInMinutes: (float, float) => int = "differenceInMinutes"

@module("date-fns") external getMinutes: Js.Date.t => int = "getMinutes"
@module("date-fns") external getHours: Js.Date.t => int = "getHours"

let nowMs = () => Js.Date.make()->getTime
