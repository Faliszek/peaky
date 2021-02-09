[@react.component]
let make = () => {
  let token = Auth.getToken();
  let url = ReasonReactRouter.useUrl();

  <ApolloClient.React.ApolloProvider client=GraphqlClient.instance>
    <div>
      {switch (token) {
       | None =>
         switch (url.path) {
         | ["calls", id, doctorId, patientId] =>
           <Call_View id patientId isPatient=true doctorId />
         | _ => <SignIn_View />
         }
       | Some(_) =>
         <Layout>
           {switch (url.path) {
            | ["patients", id, "video"] => <Patient_Video_Chat_View id />
            | ["patients", id, "chat"] => <Patient_Chat_View _id=id />
            | ["patients", id] => <Patient_Details_View id />
            | ["patients"] => <Patient_List_View />
            | ["calls", id, doctorId, patientId] =>
              <Call_View id patientId doctorId isPatient=false />
            | ["calls"] => <Calls_List_View />

            | ["consultations", id] => <Consultation_Room id />
            | ["consultations"] => <Consultations />
            | ["settings"] => <Settings />
            | [] => <Calendar />

            | _ => React.null
            }}
         </Layout>
       }}
    </div>
  </ApolloClient.React.ApolloProvider>;
};
