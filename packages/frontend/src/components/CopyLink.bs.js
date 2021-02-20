

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Text$Peaky from "./Text.bs.js";
import * as Button$Peaky from "./Button.bs.js";
import * as ReactFeather from "react-feather";

var copy = (function updateClipboard(newClip) {
  navigator.clipboard.writeText(newClip);
});

function CopyLink(Props) {
  var link = Props.link;
  var match = React.useState(function () {
        return false;
      });
  var setCopied = match[1];
  var copied = match[0];
  React.useEffect((function () {
          var timeout = setTimeout((function (param) {
                  if (copied) {
                    return Curry._1(setCopied, (function (param) {
                                  return false;
                                }));
                  }
                  
                }), 2000);
          return (function (param) {
                    setTimeout(timeout);
                    
                  });
        }), [copied]);
  return React.createElement("div", {
              className: "fixed bottom-12 right-36 mb-3"
            }, React.createElement(Button$Peaky.CTA.make, {
                  children: React.createElement(Text$Peaky.make, {
                        children: copied ? "Skopiowano!" : "Skopiuj link"
                      }),
                  className: "w-full flex items-center justify-center",
                  icon: copied ? React.createElement(ReactFeather.Check, {
                          className: "mr-4"
                        }) : React.createElement(ReactFeather.Link, {
                          className: "mr-4"
                        }),
                  type_: "ghost",
                  onClick: (function (param) {
                      Curry._1(setCopied, (function (param) {
                              return true;
                            }));
                      return copy(link);
                    })
                }));
}

var make = CopyLink;

export {
  copy ,
  make ,
  
}
/* react Not a pure module */
