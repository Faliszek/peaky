open Patient
let patient = {
  id: 1,
  firstName: j`Adam`,
  lastName: j`Smith`,
  disease: j`Depresja`,
  condition: j`Dobry`,
  avatar: Some(j`https://www.thispersondoesnotexist.com/image`),
  phoneNumber: j`+48 674 300 232`,
  lastVisit: None,
}

@react.component
let make = (~id as _id) => React.null
