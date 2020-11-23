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
