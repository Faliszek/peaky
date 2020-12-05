open Patient;
let patients: array(t) = [|
  {
    id: 1,
    firstName: {j|Adam|j},
    lastName: {j|Smith|j},
    disease: {j|Depresja|j},
    condition: {j|Dobry|j},
    avatar: Some({j|https://www.thispersondoesnotexist.com/image|j}),

    phoneNumber: {j|+48 674 300 232|j},
    lastVisit: None,
  },
  {
    id: 2,
    firstName: {j|John|j},
    lastName: {j|Malković|j},
    disease: {j|Nerwica natręctw|j},
    condition: {j|Dobry|j},
    phoneNumber: {j|+48 570 300 232|j},
    avatar: None,
    lastVisit: Some({j|22.11.2020 15:30|j}),
  },
  {
    id: 3,
    firstName: {j|John|j},
    lastName: {j|Malković|j},
    disease: {j|Nerwica natręctw|j},
    condition: {j|Dobry|j},
    phoneNumber: {j|+48 570 300 232|j},
    avatar: None,
    lastVisit: Some({j|22.11.2020 15:30|j}),
  },
  {
    id: 5,
    firstName: {j|John|j},
    lastName: {j|Malković|j},
    disease: {j|Nerwica natręctw|j},
    condition: {j|Dobry|j},
    phoneNumber: {j|+48 570 300 232|j},
    avatar: None,
    lastVisit: Some({j|22.11.2020 15:30|j}),
  },
|];

[@react.component]
let make = () => {
  <Page title="Pacjenci">
    <div>
      <div className="flex flex-wrap justify-between items-stretch">
        {patients
         ->Array.map(patient =>
             <Patient_Block patient className=" w-1/3 flex-auto mb-8 mr-12" />
           )
         ->React.array}
      </div>
    </div>
  </Page>;
};
