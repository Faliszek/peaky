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
  };
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
