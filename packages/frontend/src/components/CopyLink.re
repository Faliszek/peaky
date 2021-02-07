type timeoutID;

[@bs.val] external setTimeout: (unit => unit, int) => timeoutID = "setTimeout";

[@bs.val] external clearTimeout: timeoutID => unit = "setTimeout";

let copy = [%raw
  {|function updateClipboard(newClip) {
  navigator.clipboard.writeText(newClip);
}|}
];
[@react.component]
let make = (~link) => {
  let (copied, setCopied) = React.useState(_ => false);

  React.useEffect1(
    () => {
      let timeout =
        setTimeout(
          () =>
            if (copied) {
              setCopied(_ => false);
            },
          2000,
        );

      Some(_ => clearTimeout(timeout));
    },
    [|copied|],
  );
  <div className="fixed bottom-12 right-36 mb-3">
    <Button.CTA
      type_=`ghost
      className="w-full flex items-center justify-center"
      onClick={_ => {
        setCopied(_ => true);
        copy(link);
      }}
      icon={
        copied
          ? <Icons.Check className="mr-4" /> : <Icons.Link className="mr-4" />
      }>
      <Text> {copied ? {j|Skopiowano!|j} : {j|Skopiuj link|j}} </Text>
    </Button.CTA>
  </div>;
};
