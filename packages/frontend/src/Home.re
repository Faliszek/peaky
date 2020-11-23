module Scale = {
  [@react.component];

  let use = (~label={j|Działka M|j}, ~initialValue, ~isScale=false, ()) => {
    let step = isScale ? 0.01 : 1.0;
    let max = isScale ? "5.0" : "1050";
    let min = isScale ? "0.0" : "-1050";
    let (value, setValue) = React.useState(() => initialValue);

    let value = value->Js.Float.toString;

    let component =
      <div className="flex items-center mb-1">
        <label className="mr-4 w-16 text-center"> label->React.string </label>
        <input
          className="border px-4 py-1 rounded-xl mr-4 w-24"
          value
          onChange={e => setValue(ReactEvent.Form.target(e)##value)}
          type_="number"
        />
        <input
          step
          type_="range"
          value
          min
          max
          onChange={e => setValue(ReactEvent.Form.target(e)##value)}
        />
      </div>;

    (value, component);
  };
};

module Field = {
  [@react.component];

  let use =
      (
        ~label={j|Działka M|j},
        ~initialValue,
        ~isScale=false,
        ~scale,
        ~center,
        (),
      ) => {
    let step = isScale ? 0.01 : 1.0;
    let max = "360";
    let min = "-360";
    let (value, setValue) = React.useState(() => initialValue);

    let value = value->Js.Float.toString;

    React.useEffect1(
      () => {
        setValue(_ => initialValue);
        Js.log2(value, scale);
        None;
      },
      [|initialValue|],
    );

    let component =
      <div className="flex items-center mb-1">
        <label className="mr-4 w-16 text-center"> label->React.string </label>
        <input
          className="border px-4 py-1 rounded-xl mr-4 w-24"
          value
          onChange={e => setValue(ReactEvent.Form.target(e)##value)}
          type_="number"
        />
        <input
          step
          type_="range"
          value
          min
          max
          onChange={e => setValue(ReactEvent.Form.target(e)##value)}
        />
      </div>;

    (value, component);
  };
};

let original = "M744 -240, L757 -313, L945 -344, L944 -250, L881 -205, L709 -149z";

[@bs.val] external w: float = "innerWidth";
[@bs.val] external h: float = "innerHeight";

let moveX = 0.;

let moveY = 0.;

let oneMeterInPx = 20.598756;

let homeH = 21.62 *. oneMeterInPx;

let homeW = 26.66 *. oneMeterInPx;

let inM = v => v *. oneMeterInPx;

module Home = {
  [@react.component]
  let make = (~homeX, ~homeY, ~rotate, ~rotateY, ~rotateX) => {
    let x1 = homeX +. inM(4.0);
    let y1 = homeY +. inM(4.0);

    let x2 = x1 +. inM(8.10);
    let y2 = y1;

    let x3 = x2;
    let y3 = y2 +. inM(3.5);

    let x4 = x3 +. inM(4.6);

    let y4 = y3;

    let x5 = x4;

    let y5 = y4 +. inM(4.7);

    let x6 = x5 +. inM(3.5);

    let y6 = y5;

    let x7 = x6;

    let y7 = y6 +. inM(4.56);

    let x8 = x7 -. inM(6.9);

    let y8 = y7;

    let x9 = x8;

    let y9 = y8 -. inM(1.5);

    let x10 = x9 -. inM(7.30);

    let y10 = y9;

    let x11 = x10;

    let y11 = y10 -. inM(6.0);

    let x12 = x11 -. inM(2.0);

    let y12 = y11;

    <path
      d={j|
      M$(x1) $(y1)
      L$(x2) $(y2)
      L$(x3) $(y3)
      L$(x4) $(y4)
      L$(x5) $(y5)
      L$(x6) $(y6)
      L$(x7) $(y7)
      L$(x8) $(y8)
      L$(x9) $(y9)

      L$(x10) $(y10)
      L$(x11) $(y11)
      L$(x12) $(y12)z
      |j}
      stroke="red"
      strokeOpacity="1"
      strokeWidth="3"
      transform={j|rotate($(rotate), $(rotateX), $(rotateY))|j}
    />;
  };
};
// let h = window.innerHeight;
[@react.component]
let make = () => {
  // let (m, mInput) = Field.use(~label={j|Działka M|j}, ~initialValue="");

  let (scale, inputScale) =
    Scale.use(~label={j|Scale|j}, ~initialValue=1.0, ~isScale=true, ());

  // let (moveX, moveXInput) =
  //   Field.use(~label={j|Viewbox X|j}, ~initialValue=moveX, ());

  // let (moveY, moveYInput) =
  //   Field.use(~label={j|Viewbox Y|j}, ~initialValue=moveY, ());
  let (screenCenterX, screenCenterY) = (w /. 2.0, h /. 2.0);

  let y1 = 505.50000000000006;
  let y2 = 237.50000000000006;
  let y3 = 113.50000000000006;
  let y4 = 489.50000000000006;
  let y5 = 669.5000000000002;
  let y6 = 893.5000000000002;

  let x1 = 497.;
  let x2 = 549.;
  let x3 = 1301.;
  let x4 = 1297.;
  let x5 = 1045.;
  let x6 = 357.;

  let cx = (x1 +. x2 +. x3 +. x4 +. x5 +. x6) /. 6.;
  let cy = (y1 +. y2 +. y3 +. y4 +. y5 +. y6) /. 6.;

  let vectorX = screenCenterX -. cx;
  let vectorY = screenCenterY -. cy;

  let ((centerX, centerY), setCenter) = React.useState(() => (cx, cy));

  let y1 = 505.50000000000006 +. vectorY;
  let y2 = 237.50000000000006 +. vectorY;
  let y3 = 113.50000000000006 +. vectorY;
  let y4 = 489.50000000000006 +. vectorY;
  let y5 = 669.5000000000002 +. vectorY;
  let y6 = 893.5000000000002 +. vectorY;

  let x1 = 497. +. vectorX;
  let x2 = 549. +. vectorX;
  let x3 = 1301. +. vectorX;
  let x4 = 1297. +. vectorX;
  let x5 = 1045. +. vectorX;
  let x6 = 357. +. vectorX;

  let (y1, inputY1) =
    Field.use(~label="Y1", ~initialValue=y1, ~scale, ~center=cy, ());
  let (y2, inputY2) =
    Field.use(~label="Y2", ~initialValue=y2, ~scale, ~center=cy, ());
  let (y3, inputY3) =
    Field.use(~label="Y3", ~initialValue=y3, ~scale, ~center=cy, ());
  let (y4, inputY4) =
    Field.use(~label="Y4", ~initialValue=y4, ~scale, ~center=cy, ());
  let (y5, inputY5) =
    Field.use(~label="Y5", ~initialValue=y5, ~scale, ~center=cy, ());
  let (y6, inputY6) =
    Field.use(~label="Y6", ~initialValue=y6, ~scale, ~center=cy, ());

  let (x1, inputX1) =
    Field.use(~label="X1", ~initialValue=x1, ~scale, ~center=cx, ());
  let (x2, inputX2) =
    Field.use(~label="X2", ~initialValue=x2, ~scale, ~center=cx, ());
  let (x3, inputX3) =
    Field.use(~label="X3", ~initialValue=x3, ~scale, ~center=cx, ());
  let (x4, inputX4) =
    Field.use(~label="X4", ~initialValue=x4, ~scale, ~center=cx, ());
  let (x5, inputX5) =
    Field.use(~label="X5", ~initialValue=x5, ~scale, ~center=cx, ());
  let (x6, inputX6) =
    Field.use(~label="X6", ~initialValue=x6, ~scale, ~center=cx, ());

  let (rotate, rotateInput) =
    Field.use(~label="Rotate", ~initialValue=0.0, ~scale, ~center=cx, ());

  let y1 = y1->float_of_string +. moveY;
  let y2 = y2->float_of_string +. moveY;
  let y3 = y3->float_of_string +. moveY;
  let y4 = y4->float_of_string +. moveY;
  let y5 = y5->float_of_string +. moveY;
  let y6 = y6->float_of_string +. moveY;

  let x1 = x1->float_of_string +. moveX;
  let x2 = x2->float_of_string +. moveX;
  let x3 = x3->float_of_string +. moveX;
  let x4 = x4->float_of_string +. moveX;
  let x5 = x5->float_of_string +. moveX;
  let x6 = x6->float_of_string +. moveX;

  let d = {j|m$(x1) $(y1) L $(x2) $(y2) L $(x3) $(y3) L $(x4) $(y4) L $(x5) $(y5)  L $(x6) $(y6)z|j};

  Js.log(
    {j|


  let y1=$(y1);
  let y2=$(y2);
  let y3=$(y3);
  let y4=$(y4);
  let y5=$(y5);
  let y6=$(y6);

  let x1=$(x1);
  let x2=$(x2);
  let x3=$(x3);
  let x4=$(x4);
  let x5=$(x5);
  let x6=$(x6);




|j},
  );

  let ground =
    <path
      className="leaflet-interactive"
      stroke="#3388ff"
      strokeOpacity="1"
      strokeWidth="3"
      strokeLinecap="round"
      strokeLinejoin="round"
      fill="#3388ff"
      fillOpacity="0.2"
      fillRule="evenodd"
      d
    />;

  let center =
    <circle
      cx={(w /. 2.0)->Js.Float.toString}
      cy={(h /. 2.0)->Js.Float.toString}
      r="40"
      stroke="black"
      strokeWidth="3"
      fill="red"
    />;

  let centerGround =
    <circle
      cx={cx->Js.Float.toString}
      cy={cy->Js.Float.toString}
      r="40"
      stroke="black"
      strokeWidth="3"
      fill="blue"
    />;

  let ((homeX, homeY), setHome) = React.useState(_ => (0.0, 0.0));

  let (clicked, setClicked) = React.useState(_ => false);

  let homeCenterX = homeW /. 2.0;
  let homeCenterY = homeH /. 2.0;

  let rotateX = homeX +. homeCenterX;
  let rotateY = homeY +. homeCenterY;

  let home =
    <g>
      <rect
        className="leaflet-interactive"
        stroke="red"
        strokeOpacity="1"
        strokeWidth="3"
        fill="#3388ff"
        fillOpacity="0.2"
        width={homeW->Js.Float.toString}
        height={homeH->Js.Float.toString}
        x={homeX->Js.Float.toString}
        y={homeY->Js.Float.toString}
        transform={j|rotate($(rotate), $(rotateX), $(rotateY))|j}
      />
      <Home homeX homeY rotate rotateY rotateX />
    </g>;

  let gridPathX =
    Array.range(0, (h /. oneMeterInPx)->int_of_float + 1)
    ->Array.reduce("", (acc, current) => {
        let y = (current->float_of_int *. oneMeterInPx)->Js.Float.toString;
        let move = {j|M 0,$(y) L $(w),$(y) z \n|j};

        acc ++ move;
      });

  let gridX =
    <path
      d=gridPathX
      stroke="black"
      strokeOpacity="0.1"
      strokeWidth="1"
      strokeLinecap="round"
      strokeLinejoin="round"
    />;

  let gridPathY =
    Array.range(0, (w /. oneMeterInPx)->int_of_float + 1)
    ->Array.reduce("", (acc, current) => {
        let x = (current->float_of_int *. oneMeterInPx)->Js.Float.toString;
        let move = {j|M $(x),0 L $(x),$(h) z \n|j};

        acc ++ move;
      });

  let gridY =
    <path
      d=gridPathY
      stroke="black"
      strokeOpacity="0.1"
      strokeWidth="1"
      strokeLinecap="round"
      strokeLinejoin="round"
    />;

  <div>
    <div
      className="flex-col fixed top-0 right-0  flex items-center p-4 shadow-lg border  opacity-75"
      style={ReactDOMRe.Style.make(~backgroundColor="rgba(0,0,100,0.2)", ())}>
      rotateInput
      inputScale
    </div>
    <div
      onClick={_ => setClicked(c => !c)}
      onMouseMove={e => {
        setHome(v =>
          clicked
            ? (
              e->ReactEvent.Mouse.clientX->float_of_int -. homeCenterX,
              e->ReactEvent.Mouse.clientY->float_of_int -. homeCenterY,
            )
            : v
        )
      }}>
      <svg
        pointerEvents="none"
        className="bg-blue-200"
        viewBox={j|0 0 $(w) $(h)|j}>
        gridX
        gridY
        ground
        // center
        // centerGround
        home
      </svg>
    </div>
  </div>;
};
