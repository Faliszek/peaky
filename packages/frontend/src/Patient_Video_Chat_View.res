open Patient
let patient = {
  id: 1,
  firstName: `Adam`,
  lastName: `Smith`,
  disease: `Depresja`,
  condition: `Dobry`,
  avatar: Some(`https://www.thispersondoesnotexist.com/image`),
  phoneNumber: `+48 674 300 232`,
  lastVisit: None,
}

@react.component
let make = (~id as _id) => React.null
