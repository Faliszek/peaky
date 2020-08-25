let authenticate = (~email, ~password) => {
  Users_DTO.getByEmail(~email)
  |> Lwt.map(user => {
       switch (user) {
       | Some(user: User.DTO.t)
           when
             Bcrypt.verify(password, user.password |> Bcrypt.hash_of_string) =>
         print_endline("Auth!!!");
         Auth_DTO.createSignedToken(~id=user.id);

       | _ =>
         print_endline("Not auth");
         None;
       }
     });
};
