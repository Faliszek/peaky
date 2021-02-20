module Query = %graphql(`
  query Patients {
    patients {
      id
      firstName
      lastName
      phoneNumber
      disease
      lastVisit
      color
    }
  }
`)
