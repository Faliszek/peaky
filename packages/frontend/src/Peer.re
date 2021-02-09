type mediaStream = Js.Nullable.t(WebRTC.Media.srcObject);
module Call = {
  type call;
  type error;
  [@bs.send] external answer: (call, mediaStream) => unit = "answer";
  [@bs.send]
  external onStream: (call, string, mediaStream => unit) => unit = "on";

  [@bs.send] external onError: (call, string, error => unit) => unit = "on";
};

module Connection = {
  type t = {peer: string};

  // type d = {
  //   data: string,
  //   patientId: string,
  // };

  type receivedData = {
    patientId: option(string),
    canvas: option(string),
  };
  [@bs.send] external onOpen: (t, string, unit => unit) => unit = "on";
  // Receive messages
  [@bs.send] external onData: (t, string, receivedData => unit) => unit = "on";

  [@bs.send] external onError: (t, string, string => unit) => unit = "on";

  [@bs.send] external send: (t, receivedData) => unit = "send";
};
type t = {id: string};

type ice = {
  urls: string,
  credential: option(string),
  username: option(string),
};

type config = {iceServers: array(ice)};
type options = {
  // id: string,
  host: string,
  path: string,
  port: string,
  debug: int,
  config,
  pingInterval: int,
};
[@bs.module "peerjs"] [@bs.new]
external make: (string, options) => t = "default";

[@bs.send] external onOpen: (t, string, string => unit) => unit = "on";

[@bs.send] external onCall: (t, string, Call.call => unit) => unit = "on";

[@bs.send] external onError: (t, string, string => unit) => unit = "on";

[@bs.send] external call: (t, string, mediaStream) => unit = "call";
[@bs.send] external disconnect: t => unit = "disconnect";

type connectOpts = {serialization: string};
[@bs.send]
external connect: (t, string, connectOpts) => Connection.t = "connect";

[@bs.send]
external onConnection: (t, string, Connection.t => unit) => unit = "on";

type view =
  | Preroom
  | Meeting;

let iceServers: array(ice) = [|
  {urls: "stun:stun.l.google.com:19302", credential: None, username: None},
  {urls: "stun:stun1.l.google.com:19302", credential: None, username: None},
  // {
  //   urls: "turn:0.peerjs.com:3478",
  //   username: Some("peerjs"),
  //   credential: Some("peerjsp"),
  // },
  // {urls: "stun:stun2.l.google.com:19302", credential: None, username: None},
  // {urls: "stun:stun3.l.google.com:19302", credential: None, username: None},
|];
