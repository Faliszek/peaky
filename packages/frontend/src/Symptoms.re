type symptom = {
  id: string,
  name: string,
  date: string,
  circumstances: string,
  description: string,
  occurences: string,
  causedBy: string,
  notes: string,
};

let symptoms = [|
  {
    id: "1",
    name: {j|Kołatanie serca|j},
    date: "",
    circumstances: "",
    occurences: "",
    description: "",
    causedBy: "",
    notes: "",
  },
  {
    id: "2",
    name: {j|Arytmia|j},
    date: "",
    circumstances: "",
    occurences: "",
    description: "",
    causedBy: "",
    notes: "",
  },
|];
