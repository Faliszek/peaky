module Patient = {
  [@decco]
  type sympmtom = {
    id: string,
    name: string,
  };
  [@decco]
  type event = {
    symptomps: list(sympmtom),
    feeling: int,
    timestamp: float,
  };
  [@decco]
  type t = {
    id: string,
    firstName: string,
    lastName: string,
    phoneNumber: string,
    disease: string,
    treatment: list(event),
    color: string,
  };
  [@decco]
  type list = array(t);
};

module User = {
  [@decco]
  type t = {
    email: string,
    id: string,
    specialization: string,
    firstName: string,
    lastName: string,
    patients: option(array(Patient.t)),
  };
  [@decco];
};

module Call = {
  type t = {
    id: string,
    duration: float,
    timestamp: string,
    answered: bool,
    from_: User.t,
    to_: User.t,
  };
};

module Visit = {
  type t = {
    from_: string,
    to_: string,
    id: string,
    notes: string,
    patientId: string,
  };
};
