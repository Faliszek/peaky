type payload = {user_id: string};

[@module "jwt-decode"] external decode: option(string) => payload = "default";
