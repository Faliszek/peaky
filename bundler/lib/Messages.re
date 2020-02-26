module P = Pastel;

let discord = "https://discordapp.com/channels/235176658175262720/235176658175262720";

module Errors = {
  let noEntryPoint = <P> "Can't find " <P bold=true> "index.html" </P> </P>;

  let noFileSpecified =
    <P>
      <P bold=true color=P.RedBright> "\nNo file specified\n\n" </P>
      <P> "Are you sure you ran command corectly?\n" </P>
      <P>
        "You should specifiy entry point (in most cases, .html file) e.g. \n\n"
        <P bold=true> "\t" App.name " index.html" </P>
      </P>
    </P>;

  let cantOpenFile =
    <P>
      <P bold=true color=P.RedBright> "\nNo file specified\n\n" </P>
      <P> "Are you sure you ran command corectly?\n" </P>
      <P>
        "You should specifiy entry point (in most cases, .html file) e.g. \n\n"
        <P bold=true> "\t" App.name " index.html" </P>
      </P>
    </P>;

  let fileNoExist = (~path) =>
    <P>
      <P bold=true color=P.RedBright>
        "\nFile not exist, or you don't have permissons.\n"
      </P>
      <P>
        "Are you sure that file in path "
        <P bold=true> path </P>
        " exists?\n"
      </P>
    </P>;

  let sys = m =>
    <P>
      <P bold=true> <P color=P.Red> "!ERR " </P> m </P>
      <P>
        "\n\nThe error above might be connected with your OS, try run it again. \n"
      </P>
    </P>;

  let getHelp =
    <P>
      "If this doesn't help, come join our discord, maybe we can figure something out together.\n"
      "We are very nice people.\n\n"
      <P bold=true> discord </P>
    </P>;
};

module Info = {
  let executionTime = ms => <P> "\n✨ Execution time: " ms " ms\n" </P>;
};