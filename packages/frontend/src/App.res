@react.component
let make = () => {
  let token = Auth.getToken()
  let url = ReasonReactRouter.useUrl()

  <ApolloClient.React.ApolloProvider client=GraphqlClient.instance>
    <div>
      {switch token {
      | None =>
        switch url.path {
        | list{"calls", id, doctorId, patientId} =>
          <Call_View id patientId isPatient=true doctorId />
        | _ => <SignIn_View />
        }
      | Some(_) =>
        <Layout>
          {switch url.path {
          | list{"patients", id, "video"} => <Patient_Video_Chat_View id />
          | list{"patients", id, "chat"} => <Patient_Chat_View _id=id />
          | list{"patients", id} => <Patient_Details_View id />
          | list{"patients"} => <Patient_List_View />
          | list{"calls", id, doctorId, patientId} =>
            <Call_View id patientId doctorId isPatient=false />
          | list{"calls"} => <Calls_List_View />

          | list{"consultations", id} => <Consultation_Room id />
          | list{"consultations"} => <Consultations />
          | list{"settings"} => <Settings />
          | list{} => <Calendar />

          | _ => React.null
          }}
        </Layout>
      }}
    </div>
  </ApolloClient.React.ApolloProvider>
}
