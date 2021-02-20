module Query = %graphql(`
query Calls {
    me {
        id
    }
  calls {
     id
     duration
     timestamp
     answered
     from_ {
         id
         firstName
         lastName
     }
     to_ {
         id
       firstName
       lastName
     }
  }
}
`)
