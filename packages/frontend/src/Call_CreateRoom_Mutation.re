module Mutation = [%graphql
  {|
mutation CreateRoom($patientId: String!, $doctorId: String!) {
  createRoom(patientId: $patientId, doctorId: $doctorId){
      id
    doctorId
    patientId
  }
 }

|}
];
