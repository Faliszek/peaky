type timeoutID;

[@bs.val] external set: (unit => unit, int) => timeoutID = "setTimeout";

[@bs.val] external clear: timeoutID => unit = "setTimeout";

type intervalID;

[@bs.val]
external setInterval: (unit => unit, int) => intervalID = "setInterval";

[@bs.val] external clearInterval: intervalID => unit = "clearInterval";

type path = {
  x: float,
  y: float,
};
type point = {paths: array(path)};

// let useDebounce = (value: array(point), delay: int) => {
//   // State and setters for debounced value
//   let (debouncedValue, setDebouncedValue) = React.useState(_ => value);

//   React.useEffect2(
//     () => {
//       // Update debounced value after delay
//       let handler = set(() => {setDebouncedValue(_ => value)}, delay);

//       // Cancel the timeout if value changes (also on delay change or unmount)
//       // This is how we prevent debounced value from updating if value is changed ...
//       // .. within the delay period. Timeout gets cleared and restarted.
//       Some(() => {clear(handler)});
//     },
//     (value, delay) // Only re-call effect if value or delay changes
//   );

//   debouncedValue;
// };

[@bs.module "use-debounce"]
external useDebounce: (array(point), int) => array(array(point)) =
  "useDebounce";
