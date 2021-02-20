module Query = %graphql(`
    query Patient($id: String!) {

        patient(id: $id) {
          id
          firstName
          lastName
          phoneNumber
          disease
          lastVisit
          color
        }
        calls {
          id
          duration
          timestamp
          answered
          to_ {
            firstName
            lastName
          }
        }
        symptoms(patientId: $id) {
          id
          name
          date
          circumstances
          description
          occurences
          causedBy
          notes
          color
        }

        patientEvents(patientId: $id) {
          id
          symptompId
          feeling
          timestamp

        }
        feelings(patientId: $id) {
          id
          patientId
          value
          timestamp
        }


}
`)
