module Query = [%graphql
  {|
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
}
|}
];
