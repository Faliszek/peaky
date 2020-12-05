var ws = require("ws");
var express = require("express");
var uuid = require("node-uuid");

// var requests = {};

const app = express();

// var webSocket = new ws("ws://localhost:5000/");
// webSocket.on("open", function () {
//   console.log("Connected!");
// });

// webSocket.on("message", function (args) {
//   //   var json = JSON.parse(data);
//   console.log("Message", arguments);
//   //   var res = requests[json.requestId];
//   //   res.setHeader("content-type", "text/javascript");
//   //   res.send(json.data);
//   //   delete requests[json.requestId];
// });
const { exec, spawn } = require("child_process");

// var server = app.listen(3000, function () {
//   var port = server.address().port;
//   console.log("Listening at %s", port);
// });

process.release.name = "DUPA";
console.log("My pid: ", process.pid, process.cwd());

const bsb = exec("./node_modules/.bin/bsb -make-world -w");

console.log("Bsb pid: ", bsb.stdout);

bsb.stdout.on("data", function () {
  console.log("_______________________________________");
  console.log(`Received chunk`, arguments);
});

bsb.on("exit", () =>
  console.log("________________________DONE_______________________")
);

// bsb.on("close", () => console.log("close", arguments));
// bsb.on("disconnect", () => console.log("disconnect", arguments));
// bsb.on("error", () => console.log("error", arguments));
// bsb.on("exit", () => console.log("exit", arguments));
// bsb.on("message", () => console.log("message", arguments));
// bsb.on("data", (err, stdout, stderr) => {
//   if (err) {
//     console.error(err);
//     return;
//   }
//   console.log(stdout);
// });

// bsb.on("beforeExit", (code) => {
//   console.log("Process beforeExit event with code: ", code);
// });

// bsb.on("exit", (code) => {
//   console.log("Process exit event with code: ", code);
// });

setInterval(() => {}, 1 << 30);
