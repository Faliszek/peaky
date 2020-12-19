module MediaDevices = {
  module Constraints = {
    type t = {
      audio: bool,
      video: bool,
    };
  };
  type constraints;
  type stream;

  [@bs.scope ("window", "navigator", "mediaDevices")] [@bs.val]
  external getUserMedia: Constraints.t => Promise.t(stream) = "getUserMedia";
};
