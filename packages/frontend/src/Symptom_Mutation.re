module Mutation = [%graphql
  {|
mutation AddSyptom($patientId: String!, $name: String!, $date: String!, $circumstances: String!, $description: String!, $occurences: String!,  $causedBy: String!, $notes: String!, $color: String!) {
  addSymptom(patientId: $patientId, name: $name, date: $date, circumstances: $circumstances, description: $description, occurences: $occurences, causedBy: $causedBy, notes: $notes, color: $color){
    id
    name
    date
    circumstances
    description
    occurences
    causedBy
    notes
  }
}

|}
];
