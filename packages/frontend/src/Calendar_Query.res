module Query = %graphql(`
    query Visits {
      visits {
        id
        from_
        to_
        patientId
      }

      patients {
        id
        firstName
        lastName
        disease
        color
      }
    }
  `)
