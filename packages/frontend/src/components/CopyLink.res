let copy = %raw(`function updateClipboard(newClip) {
  navigator.clipboard.writeText(newClip);
}`)
@react.component
let make = (~link) => {
  let (copied, setCopied) = React.useState(_ => false)

  React.useEffect1(() => {
    let timeout = Timeout.set(() =>
      if copied {
        setCopied(_ => false)
      }
    , 2000)

    Some(_ => Timeout.clear(timeout))
  }, [copied])
  <div className="fixed bottom-12 right-36 mb-3">
    <Button.CTA
      type_=#ghost
      className="w-full flex items-center justify-center"
      onClick={_ => {
        setCopied(_ => true)
        copy(link)
      }}
      icon={copied ? <Icons.Check className="mr-4" /> : <Icons.Link className="mr-4" />}>
      <Text> {copied ? j`Skopiowano!` : j`Skopiuj link`} </Text>
    </Button.CTA>
  </div>
}
