type config = {
  apiKey: string,
  authDomain: string,
  databaseURL: string,
  projectId: string,
  storageBucket: string,
  messagingSenderId: string,
  appId: string,
};

[@bs.module "firebase"] external make: config => unit = "initializeApp";

module Database = {
  type ref('a) = {set: Js.t('a)};

  type t;
  [@bs.module "firebase"] external make: unit => t = "database";
  //   [@bs.module "firebase"] external make: unit => unit = "database";
};
