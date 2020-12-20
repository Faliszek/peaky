open Select;
let all = [|
  {value: "1", label: {j|Alergologia|j}},
  {value: "2", label: {j|Anestezjologia i intensywna terapia|j}},
  {value: "3", label: {j|Angiologia|j}},
  {value: "4", label: {j|Audiologia i foniatria|j}},
  {value: "5", label: {j|Balneologia i medycyna fizykalna|j}},
  {value: "6", label: {j|Chirurgia dziecięca|j}},
  {value: "7", label: {j|Chirurgia klatki piersiowej|j}},
  {value: "8", label: {j|Chirurgia naczyniowa|j}},
  {value: "9", label: {j|Chirurgia ogólna|j}},
  {value: "10", label: {j|Chirurgia onkologiczna|j}},
  {value: "11", label: {j|Chirurgia plastyczna|j}},
  {value: "12", label: {j|Chirurgia szczękowo-twarzowa|j}},
  {value: "13", label: {j|Choroby płuc|j}},
  {value: "14", label: {j|Choroby płuc dzieci|j}},
  {value: "15", label: {j|Choroby wewnętrzne|j}},
  {value: "16", label: {j|Choroby zakaźne|j}},
  {value: "17", label: {j|Dermatologia i wenerologia|j}},
  {value: "18", label: {j|Diabetologia|j}},
  {value: "19", label: {j|Diagnostyka laboratoryjna|j}},
  {value: "20", label: {j|Endokrynologia|j}},
  {value: "21", label: {j|Endokrynologia ginekologiczna i rozrodczość|j}},
  {value: "22", label: {j|Endokrynologia i diabetologia dziecięca|j}},
  {value: "23", label: {j|Epidemiologia|j}},
  {value: "24", label: {j|Farmakologia kliniczna|j}},
  {value: "25", label: {j|Gastroenterologia|j}},
  {value: "26", label: {j|Gastroenterologia dziecięca|j}},
  {value: "27", label: {j|Genetyka kliniczna|j}},
  {value: "28", label: {j|Geriatria|j}},
  {value: "29", label: {j|Ginekologia onkologiczna|j}},
  {value: "30", label: {j|Hematologia|j}},
  {value: "31", label: {j|Hipertensjologia|j}},
  {value: "32", label: {j|Immunologia kliniczna|j}},
  {value: "33", label: {j|Intensywna terapia|j}},
  {value: "34", label: {j|Kardiochirurgia|j}},
  {value: "35", label: {j|Kardiologia|j}},
  {value: "36", label: {j|Kardiologia dziecięca|j}},
  {value: "37", label: {j|Medycyna lotnicza|j}},
  {value: "38", label: {j|Medycyna morska i tropikalna|j}},
  {value: "39", label: {j|Medycyna nuklearna|j}},
  {value: "40", label: {j|Medycyna paliatywna|j}},
  {value: "41", label: {j|Medycyna pracy|j}},
  {value: "42", label: {j|Medycyna ratunkowa|j}},
  {value: "43", label: {j|Medycyna rodzinna|j}},
  {value: "44", label: {j|Medycyna sądowa|j}},
  {value: "45", label: {j|Medycyna sportowa|j}},
  {value: "46", label: {j|Mikrobiologia lekarska|j}},
  {value: "47", label: {j|Nefrologia|j}},
  {value: "48", label: {j|Nefrologia dziecięca|j}},
  {value: "49", label: {j|Neonatologia|j}},
  {value: "50", label: {j|Neurochirurgia|j}},
  {value: "51", label: {j|Neurologia|j}},
  {value: "52", label: {j|Neurologia dziecięca|j}},
  {value: "53", label: {j|Neuropatologia|j}},
  {value: "54", label: {j|Okulistyka|j}},
  {value: "55", label: {j|Onkologia i hematologia dziecięca|j}},
  {value: "56", label: {j|Onkologia kliniczna|j}},
  {value: "57", label: {j|Ortopedia i traumatologia narządu ruchu|j}},
  {value: "58", label: {j|Otorynolaryngologia|j}},
  {value: "59", label: {j|Otorynolaryngologia dziecięca|j}},
  {value: "60", label: {j|Patomorfologia|j}},
  {value: "61", label: {j|Pediatria|j}},
  {value: "62", label: {j|Pediatria metaboliczna|j}},
  {value: "63", label: {j|Perinatologia|j}},
  {value: "64", label: {j|Położnictwo i ginekologia|j}},
  {value: "65", label: {j|Psychiatria|j}},
  {value: "66", label: {j|Psychiatria dzieci i młodzieży|j}},
  {value: "67", label: {j|Radiologia i diagnostyka obrazowa|j}},
  {value: "68", label: {j|Radioterapia onkologiczna|j}},
  {value: "69", label: {j|Rehabilitacja medyczna|j}},
  {value: "70", label: {j|Reumatologia|j}},
  {value: "71", label: {j|Seksuologia|j}},
  {value: "72", label: {j|Toksykologia kliniczna|j}},
  {value: "73", label: {j|Transfuzjologia kliniczna|j}},
  {value: "74", label: {j|Transplantologia kliniczna|j}},
  {value: "75", label: {j|Urologia|j}},
  {value: "76", label: {j|Urologia dziecięca|j}},
|];
