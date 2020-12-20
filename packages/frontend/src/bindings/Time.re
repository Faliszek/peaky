let now = () => Js.Date.make();

[@bs.module "date-fns"]
external addDays: (Js.Date.t, int) => Js.Date.t = "addDays";

[@bs.module "date-fns"]
external addHours: (Js.Date.t, int) => Js.Date.t = "addHours";

[@bs.module "date-fns"]
external subDays: (Js.Date.t, int) => Js.Date.t = "subDays";

[@bs.module "date-fns"]
external subHours: (Js.Date.t, int) => Js.Date.t = "subHours";

[@bs.module "date-fns"]
external format: (Js.Date.t, string) => string = "format";

[@bs.module "date-fns"] external getTime: Js.Date.t => float = "getTime";

[@bs.module "date-fns"]
external startOfDay: Js.Date.t => Js.Date.t = "startOfDay";
