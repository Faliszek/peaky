open Patient;
let patient = {
  id: 1,
  firstName: {j|Adam|j},
  lastName: {j|Smith|j},
  disease: {j|Depresja|j},
  condition: {j|Dobry|j},
  avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),

  phoneNumber: {j|+48 674 300 232|j},
  lastVisit: None,
};

[@react.component]
let make = (~id as _id) => {
  React.null;
};
