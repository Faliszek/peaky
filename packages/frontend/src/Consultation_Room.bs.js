

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import Peerjs from "peerjs";
import * as Belt_Array from "@rescript/std/lib/es6/belt_Array.js";
import * as Peer$Peaky from "./Peer.bs.js";
import * as Belt_Option from "@rescript/std/lib/es6/belt_Option.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as WebRTC$Peaky from "./WebRTC.bs.js";
import * as Spinner$Peaky from "./components/Spinner.bs.js";
import * as ReactFeather from "react-feather";
import * as Client from "@apollo/client";
import * as Call_View_Preroom$Peaky from "./Call_View_Preroom.bs.js";
import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";
import * as Consultation_Room_PatientView$Peaky from "./Consultation_Room_PatientView.bs.js";

var Raw = {};

var query = Client.gql("query Consultation($id: String!)  {\nme  {\n__typename  \nid  \n}\n\nusers  {\n__typename  \nid  \nfirstName  \nlastName  \n}\n\nconsultation(id: $id)  {\n__typename  \nid  \ncallerId  \nuserIds  \n}\n\n}\n");

function parse(value) {
  var value$1 = value.me;
  var value$2 = value.users;
  var value$3 = value.consultation;
  var tmp;
  if (value$3 == null) {
    tmp = undefined;
  } else {
    var value$4 = value$3.userIds;
    tmp = {
      __typename: value$3.__typename,
      id: value$3.id,
      callerId: value$3.callerId,
      userIds: value$4.map(function (value) {
            return value;
          })
    };
  }
  return {
          me: {
            __typename: value$1.__typename,
            id: value$1.id
          },
          users: value$2.map(function (value) {
                return {
                        __typename: value.__typename,
                        id: value.id,
                        firstName: value.firstName,
                        lastName: value.lastName
                      };
              }),
          consultation: tmp
        };
}

function serialize(value) {
  var value$1 = value.consultation;
  var consultation;
  if (value$1 !== undefined) {
    var value$2 = value$1.userIds;
    var userIds = value$2.map(function (value) {
          return value;
        });
    var value$3 = value$1.callerId;
    var value$4 = value$1.id;
    var value$5 = value$1.__typename;
    consultation = {
      __typename: value$5,
      id: value$4,
      callerId: value$3,
      userIds: userIds
    };
  } else {
    consultation = null;
  }
  var value$6 = value.users;
  var users = value$6.map(function (value) {
        var value$1 = value.lastName;
        var value$2 = value.firstName;
        var value$3 = value.id;
        var value$4 = value.__typename;
        return {
                __typename: value$4,
                id: value$3,
                firstName: value$2,
                lastName: value$1
              };
      });
  var value$7 = value.me;
  var value$8 = value$7.id;
  var value$9 = value$7.__typename;
  var me = {
    __typename: value$9,
    id: value$8
  };
  return {
          me: me,
          users: users,
          consultation: consultation
        };
}

function serializeVariables(inp) {
  return {
          id: inp.id
        };
}

function makeVariables(id, param) {
  return {
          id: id
        };
}

var ConsultationsQuery_inner = {
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables
};

var include = ApolloClient__React_Hooks_UseQuery.Extend({
      query: query,
      Raw: Raw,
      parse: parse,
      serialize: serialize,
      serializeVariables: serializeVariables
    });

var use = include.use;

var ConsultationsQuery_refetchQueryDescription = include.refetchQueryDescription;

var ConsultationsQuery_useLazy = include.useLazy;

var ConsultationsQuery_useLazyWithVariables = include.useLazyWithVariables;

var ConsultationsQuery = {
  ConsultationsQuery_inner: ConsultationsQuery_inner,
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  refetchQueryDescription: ConsultationsQuery_refetchQueryDescription,
  use: use,
  useLazy: ConsultationsQuery_useLazy,
  useLazyWithVariables: ConsultationsQuery_useLazyWithVariables
};

function useConsultation(peer, userIds, localStream, setStreams, streams) {
  React.useEffect((function () {
          var call = function (param) {
            if (streams.length === userIds.length) {
              return ;
            } else {
              Belt_Array.map(userIds, (function (userId) {
                      peer.call(userId, localStream);
                      
                    }));
              return ;
            }
          };
          call(undefined);
          peer.on("error", (function (_err) {
                  return call(undefined);
                }));
          peer.on("call", (function (call) {
                  call.answer(localStream);
                  call.on("stream", (function (remoteStream) {
                          if (remoteStream == null) {
                            console.log("no Stream");
                            return ;
                          } else {
                            return Curry._1(setStreams, (function (streams) {
                                          if (Belt_Option.isSome(Belt_Array.get(Belt_Array.keep(streams, (function (x) {
                                                            return x.id === remoteStream.id;
                                                          })), 0))) {
                                            return streams;
                                          } else {
                                            return Belt_Array.concat(streams, [remoteStream]);
                                          }
                                        }));
                          }
                        }));
                  
                }));
          
        }), []);
  
}

function Consultation_Room$Video(Props) {
  var stream = Props.stream;
  return React.createElement("video", {
              ref: (function (el) {
                  return WebRTC$Peaky.setVideo(el, stream, true);
                }),
              className: "shadow-xl rounded-xl flex-1 transform border-2 border-gray bg-black",
              style: {
                transform: "scale(-1, 1)"
              }
            });
}

var Video = {
  make: Consultation_Room$Video
};

function Consultation_Room$Meeting(Props) {
  var dataMyId = Props.dataMyId;
  var callerId = Props.callerId;
  var userIds = Props.userIds;
  var localStream = Props.localStream;
  var media = Props.media;
  var setMedia = Props.setMedia;
  var peer = Props.peer;
  var dataPeer = Props.dataPeer;
  var dataUserIds = Props.dataUserIds;
  var match = React.useState(function () {
        return [];
      });
  var streams = match[0];
  useConsultation(peer, userIds, localStream, match[1], streams);
  return React.createElement("div", undefined, React.createElement("div", {
                  className: "flex w-full h-screen  overflow-hidden"
                }, React.createElement("div", {
                      className: "w-1/2 flex items-center justify-center gap-4 flex-col"
                    }, Belt_Array.map(streams, (function (stream) {
                            return React.createElement(Consultation_Room$Video, {
                                        stream: stream,
                                        key: stream.id
                                      });
                          }))), React.createElement("div", {
                      className: "w-1/2 flex items-center justify-center overflow-y-scroll"
                    }, React.createElement(Consultation_Room_PatientView$Peaky.make, {
                          callerId: callerId,
                          myId: dataMyId,
                          userIds: dataUserIds,
                          peer: dataPeer
                        }))), React.createElement("div", {
                  className: "w-64 h-32 fixed left-40 ml-12 top-12 bg-black flex items-center rounded-xl justify-center"
                }, React.createElement("video", {
                      ref: (function (el) {
                          return WebRTC$Peaky.setVideo(el, localStream, true);
                        }),
                      className: "transform rounded-xl border-2 border-gray bg-black",
                      style: {
                        transform: "scale(-1, 1)"
                      }
                    }), React.createElement("div", {
                      className: "flex justify-around gap-4 absolute bottom-2 w-full"
                    }, React.createElement(Button$Peaky.CallButton.make, {
                          icon: media.audio ? React.createElement(ReactFeather.Mic, {
                                  size: "16"
                                }) : React.createElement(ReactFeather.MicOff, {
                                  size: "16"
                                }),
                          onClick: (function (param) {
                              return Curry._1(setMedia, {
                                          TAG: /* SetAudio */0,
                                          _0: !media.audio
                                        });
                            }),
                          className: "bg-white  text-gray-600 hover:bg-gray-100"
                        }), React.createElement(Button$Peaky.CallButton.make, {
                          icon: media.video ? React.createElement(ReactFeather.Video, {
                                  size: "16"
                                }) : React.createElement(ReactFeather.VideoOff, {
                                  size: "16"
                                }),
                          onClick: (function (param) {
                              return Curry._1(setMedia, {
                                          TAG: /* SetVideo */1,
                                          _0: !media.video
                                        });
                            }),
                          className: "bg-white text-gray-600  hover:bg-gray-100"
                        }), React.createElement(Button$Peaky.CallButton.make, {
                          icon: React.createElement(ReactFeather.Phone, {
                                size: "16"
                              }),
                          onClick: (function (param) {
                              peer.disconnect();
                              
                            }),
                          className: "bg-red-400 text-white  hover:bg-red-300"
                        }))));
}

var Meeting = {
  make: Consultation_Room$Meeting
};

function Consultation_Room(Props) {
  var id = Props.id;
  var query = Curry.app(use, [
        undefined,
        undefined,
        undefined,
        undefined,
        /* NetworkOnly */3,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        {
          id: id
        }
      ]);
  var match = WebRTC$Peaky.use(undefined);
  var setMedia = match[2];
  var media = match[1];
  var stream = match[0];
  var match$1 = React.useState(function () {
        
      });
  var setPeer = match$1[1];
  var peer = match$1[0];
  var match$2 = React.useState(function () {
        
      });
  var setDataPeer = match$2[1];
  var dataPeer = match$2[0];
  var match$3 = React.useState(function () {
        return /* Room */0;
      });
  var setView = match$3[1];
  React.useEffect((function () {
          var match = query.data;
          if (match !== undefined && dataPeer === undefined) {
            var me = match.me;
            Curry._1(setDataPeer, (function (param) {
                    return new Peerjs("data" + me.id, {
                                host: "localhost",
                                path: "/calls",
                                port: "9000",
                                debug: 0,
                                config: {
                                  iceServers: Peer$Peaky.iceServers
                                },
                                pingInterval: 5000
                              });
                  }));
          }
          var match$1 = query.data;
          if (match$1 !== undefined && peer === undefined) {
            var me$1 = match$1.me;
            Curry._1(setPeer, (function (param) {
                    return new Peerjs("media" + me$1.id, {
                                host: "localhost",
                                path: "/calls",
                                port: "9000",
                                debug: 0,
                                config: {
                                  iceServers: Peer$Peaky.iceServers
                                },
                                pingInterval: 5000
                              });
                  }));
          }
          
        }), [
        query.data,
        peer,
        dataPeer
      ]);
  var match$4 = query.data;
  if (query.loading) {
    return React.createElement("div", {
                className: "flex items-center justify-center w-full h-screen"
              }, React.createElement(Spinner$Peaky.make, {}));
  }
  if (match$4 === undefined) {
    return null;
  }
  var match$5 = match$4.consultation;
  if (match$5 === undefined) {
    return null;
  }
  if (dataPeer === undefined) {
    return null;
  }
  if (peer === undefined) {
    return null;
  }
  var userIds = match$5.userIds;
  var callerId = match$5.callerId;
  var me = match$4.me;
  var myId = me.id;
  var dataMyId = "data" + me.id;
  var mediaUserIds = Belt_Array.map(Belt_Array.keep(Belt_Array.concat(userIds, [callerId]), (function (u) {
              return u !== myId;
            })), (function (u) {
          return "media" + u;
        }));
  var dataUserIds = Belt_Array.map(Belt_Array.keep(Belt_Array.concat(userIds, [callerId]), (function (u) {
              return u !== myId;
            })), (function (u) {
          return "data" + u;
        }));
  if (match$3[0]) {
    return React.createElement(Consultation_Room$Meeting, {
                dataMyId: dataMyId,
                callerId: callerId,
                userIds: mediaUserIds,
                localStream: stream,
                media: media,
                setMedia: setMedia,
                peer: peer,
                dataPeer: dataPeer,
                dataUserIds: dataUserIds
              });
  } else {
    return React.createElement(Call_View_Preroom$Peaky.make, {
                stream: stream,
                media: media,
                setMedia: setMedia,
                onJoin: (function (param) {
                    return Curry._1(setView, (function (param) {
                                  return /* Consulting */1;
                                }));
                  }),
                loading: false
              });
  }
}

var make = Consultation_Room;

export {
  ConsultationsQuery ,
  useConsultation ,
  Video ,
  Meeting ,
  make ,
  
}
/* query Not a pure module */
