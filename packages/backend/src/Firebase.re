module Error = {
  type t('e) = Js.t('e);
};

module Database = {
  type t;
  module rec Reference: {
    type t;
    [@bs.get] external key: t => Js.Nullable.t(string) = "key";
    [@bs.get] external parent: t => Js.Nullable.t(t) = "parent";
    [@bs.get] external root: t => t = "root";
    [@bs.send] external child: (t, ~path: string) => t = "child";
    type cb = DataSnapshot.t => unit;
    [@bs.send]
    external once:
      (
        t,
        ~eventType: string,
        ~successCallback: cb=?,
        ~failureCallbackOrContext: Error.t('e) => unit=?,
        unit
      ) =>
      Promise.Js.t(DataSnapshot.t, Js.Promise.error) =
      "once";
    [@bs.send]
    external on:
      (
        t,
        ~eventType: string,
        ~callback: cb,
        ~cancelCallback: Error.t('e) => unit=?,
        unit
      ) =>
      cb =
      "on";
    [@bs.send]
    external off: (t, ~eventType: string, ~callback: cb=?, unit) => unit =
      "off";
    [@bs.send]
    external set:
      (
        t,
        ~value: 'a,
        ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?,
        unit
      ) =>
      Promise.Js.t(unit, Js.Promise.error) =
      "set";
    [@bs.send]
    external update:
      (
        t,
        ~value: 'a,
        ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?,
        unit
      ) =>
      Promise.Js.t(unit, Js.Promise.error) =
      "update";
    [@bs.send]
    external push:
      (
        t,
        ~value: 'a=?,
        ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?,
        unit
      ) =>
      t =
      "push";
  } = Reference
  and DataSnapshot: {
    type t;
    [@bs.get] external key: t => Js.Null.t(string) = "key";
    [@bs.get] external ref: t => Reference.t = "ref";
    [@bs.send] external child: (t, ~path: string) => t = "child";
    [@bs.send] external exists: t => bool = "exists";
    [@bs.send] external exportVal: t => Js.Json.t = "exportVal";
    [@bs.send] external foreach: (t, t => bool) => bool = "forEach";
    /*external getPriority*/
    [@bs.send] external hasChild: (t, ~path: string) => bool = "hasChild";
    [@bs.send] external hasChildren: t => bool = "hasChildren";
    [@bs.send] external numChildren: t => int = "numChildren";
    [@bs.send] external toJson: t => Js.Json.t = "toJSON";
    [@bs.send] external val_: t => Js.Json.t = "val";
  } = DataSnapshot;
  module OnDisconnect = {
    type t;
    [@bs.send]
    external cancel:
      (t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Promise.Js.t(unit, Js.Promise.error) =
      "cancel";
    [@bs.send]
    external remove:
      (t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Promise.Js.t(unit, Js.Promise.error) =
      "remove";
    [@bs.send]
    external set:
      (t, Js.Json.t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Promise.Js.t(unit, Js.Promise.error) =
      "set";
    /*external setWithPriority*/
    [@bs.send]
    external update:
      (t, Js.Json.t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Promise.Js.t(unit, Js.Promise.error) =
      "update";
  };
  module ThenableReference = {
    type t;
  };
  module Query = {
    type t;
  };
  [@bs.send] external goOffline: t => unit = "goOffline";
  [@bs.send] external goOnline: t => unit = "goOnline";
  [@bs.send] external ref: (t, ~path: string=?, unit) => Reference.t = "ref";
  [@bs.send]
  external refFromURL: (t, ~url: string) => Reference.t = "refFromURL";
  [@bs.val] [@bs.module "firebase"] [@bs.scope ("database", "ServerValue")]
  external serverTimestamp: Js.Null.t(string) = "TIMESTAMP";
};

module Storage = {
  type t;
  module UploadTask = {
    type t;
  };
  module Reference = {
    type t;
    [@bs.get] external bucket: t => string = "bucket";
    [@bs.get] external fullPath: t => string = "fullPath";
    [@bs.get] external name: t => string = "name";
    [@bs.get] external parent: t => option(t) = "parent";
    [@bs.get] external root: t => t = "root";
    [@bs.send] external path: (t, ~path: string) => t = "path";
    // [@bs.send]
    // external put:
    //   (t, ~data: Fetch.blob, ~metadata: Js.t('a)=?, unit) =>
    //   Promise.Js.t(UploadTask.t, Js.Promise.error) =
    //   "put";
    [@bs.send]
    external delete: t => Promise.Js.t(unit, Js.Promise.error) = "delete";
    [@bs.send]
    external getDownloadURL: t => Promise.Js.t(string, Js.Promise.error) =
      "getDownloadURL";
  };

  [@bs.send] external ref: (t, ~path: string=?, unit) => Reference.t = "ref";
};

module Auth = {
  type t;

  module User = {
    type t = {
      uid: string,
      email: string,
    };
    type profile = {
      displayName: option(string),
      photoURL: option(string),
    };

    [@bs.get] external displayName: t => string = "displayName";
    [@bs.get] external email: t => Js.Nullable.t(string) = "email";
    [@bs.get] external emailVerified: t => bool = "emailVerified";
    [@bs.get] external isAnonymous: t => bool = "isAnonymous";
    [@bs.get]
    external phoneNumber: t => Js.Nullable.t(string) = "phoneNumber";
    [@bs.get] external photoURL: t => Js.Nullable.t(string) = "photoURL";
    [@bs.get] external uid: t => string = "uid";
    [@bs.send]
    external updateProfile:
      (t, ~profile: profile) => Promise.Js.t(unit, Js.Promise.error) =
      "updateProfile";
    [@bs.send]
    external getIdToken:
      t => Promise.Js.t(Js.Nullable.t(string), Js.Promise.error) =
      "getIdToken";
  };

  module Provider = {
    type t;

    [@bs.deriving abstract]
    type token = {accessToken: string};

    [@bs.new] [@bs.module "firebase"] [@bs.scope "auth"]
    external googleAuthProvider: unit => t = "GoogleAuthProvider";

    [@bs.new] [@bs.module "firebase"] [@bs.scope "auth"]
    external facebookAuthProvider: unit => t = "FacebookAuthProvider";

    [@bs.send] external credential: (t, token) => t = "credential";
  };

  [@bs.get] external currentUser: t => Js.Nullable.t(User.t) = "currentUser";

  type ubsubscribe = unit => unit;

  [@bs.send]
  external onAuthStateChanged:
    (
      t,
      ~nextOrObserver: Js.Null.t(User.t) => unit,
      ~error: Error.t('e) => unit=?,
      ~completed: unit => unit=?,
      unit
    ) =>
    ubsubscribe =
    "onAuthStateChanged";
  // [@bs.send]
  // external signInAnonymously:
  //   (t, unit) => Promise.Js.t(User.t, Js.Promise.error) =
  //   "signInAnonymously";
  // [@bs.send]
  // external signInWithCredential:
  //   (t, ~credential: Provider.t) => Promise.Js.t(User.t, Js.Promise.error) =
  //   "signInWithCredential";

  type createUserWithEmailAndPasswordError = {
    code: string,
    message: string,
  };

  type signInResponse = {user: User.t};

  type signUpResponse = {user: User.t};
  [@bs.send]
  external createUserWithEmailAndPassword:
    (t, ~email: string, ~password: string) =>
    Promise.Js.t(signUpResponse, Js.Promise.error) =
    "createUserWithEmailAndPassword";

  [@bs.send]
  external signInWithEmailAndPassword:
    (t, ~email: string, ~password: string) =>
    Promise.Js.t(signInResponse, Js.Promise.error) =
    "signInWithEmailAndPassword";
  // [@bs.send]
  // external signInWithCustomToken:
  //   (t, ~token: string) => Promise.Js.t(User.t, Js.Promise.error) =
  // "signInWithCustomToken";
  [@bs.send]
  external signOut: t => Promise.Js.t(unit, Js.Promise.error) = "signOut";

  type sendPasswordResetEmailError = {code: string};

  [@bs.send]
  external sendPasswordResetEmail:
    (t, ~email: string) => Promise.Js.t(unit, sendPasswordResetEmailError) =
    "sendPasswordResetEmail";
};

module App = {
  type t;
  [@bs.send] external auth: t => Auth.t = "auth";
  [@bs.send] external database: t => Database.t = "database";
  /*external delete*/
  /*external messaging*/
  [@bs.send] external storage: t => Storage.t = "storage";
  [@bs.get] external options: t => Js.t('a) = "options";
};

type options = {
  apiKey: string,
  authDomain: string,
  databaseURL: string,
  projectId: string,
  storageBucket: string,
  messagingSenderId: string,
  appId: string,
};

[@bs.module "firebase"]
external initializeApp: (~options: options) => App.t = "initializeApp";

[@bs.module "firebase"] external app: (~name: string=?) => App.t = "app";

[@bs.module "firebase"] external apps: array(App.t) = "apps";

[@bs.module "firebase"] external auth: App.t => Auth.t = "auth";

[@bs.module "firebase"] external database: App.t => Database.t = "database";
