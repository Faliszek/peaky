type view =
  | Preroom
  | Meeting
@react.component
let make = (~id as callId, ~patientId, ~doctorId, ~isPatient) => {
  let (stream, media, setMedia) = WebRTC.use()

  let (mutation, result) = Call_CreateRoom_Mutation.Mutation.use()

  let (view, setView) = React.useState(_ => Preroom)

  switch isPatient {
  //DOCTOR
  | false =>
    let userId = Auth.getUserId()

    <div className="flex flex-col h-screen w-full relative">
      {switch view {
      | Preroom =>
        <Call_View_Preroom
          stream
          media
          setMedia
          loading=result.loading
          onJoin={_ =>
            mutation({doctorId: userId, patientId: patientId})->Request.onFinish(
              ~onError=_ => (),
              ~onOk=({createRoom}) =>
                switch createRoom {
                | Some(_) => setView(_ => Meeting)
                | None => ()
                },
            )}
        />
      | Meeting =>
        <Call_View_Meeting callId doctorId isPatient localStream=stream media patientId setMedia />
      }}
    </div>

  | true =>
    <div className="flex flex-col h-screen w-full relative">
      {switch view {
      | Preroom =>
        <Call_View_Preroom
          loading=false stream media setMedia onJoin={_ => setView(_ => Meeting)}
        />
      | Meeting =>
        <Call_View_Meeting callId doctorId isPatient localStream=stream media patientId setMedia />
      }}
    </div>
  }
}
