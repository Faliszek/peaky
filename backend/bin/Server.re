open Lib;

Console.log(<Pastel bold=true> "Starting server ...\n" </Pastel>);
Db.init();
Server.run();