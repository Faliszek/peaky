module Mutation = %graphql(`
  mutation createVisit($patientId: String!, $from_: String!, $to_: String!, $notes: String) {
    createVisit(
      patientId: $patientId,
      from_: $from_,
      to_: $to_,
      notes: $notes,

      ){
        id
      }
  }
`)
