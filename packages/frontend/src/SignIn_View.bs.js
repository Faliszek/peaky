

import * as Curry from "@rescript/std/lib/es6/curry.js";
import * as React from "react";
import * as Formality from "re-formality/src/Formality.bs.js";
import * as Auth$Peaky from "./Auth.bs.js";
import * as Text$Peaky from "./components/Text.bs.js";
import * as Caml_option from "@rescript/std/lib/es6/caml_option.js";
import * as Input$Peaky from "./components/Input.bs.js";
import * as Button$Peaky from "./components/Button.bs.js";
import * as Loader$Peaky from "./components/Loader.bs.js";
import * as Router$Peaky from "./Router.bs.js";
import * as Request$Peaky from "./Request.bs.js";
import * as Client from "@apollo/client";
import * as Graphic_Login$Peaky from "./graphics/Graphic_Login.bs.js";
import * as Formality__ReactUpdate from "re-formality/src/Formality__ReactUpdate.bs.js";
import * as ApolloClient__React_Hooks_UseMutation from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseMutation.bs.js";

var Raw = {};

var query = Client.gql("mutation SignIn($email: String!, $password: String!)  {\nsignIn(email: $email, password: $password)  \n}\n");

function parse(value) {
  var value$1 = value.signIn;
  return {
          signIn: !(value$1 == null) ? value$1 : undefined
        };
}

function serialize(value) {
  var value$1 = value.signIn;
  var signIn = value$1 !== undefined ? value$1 : null;
  return {
          signIn: signIn
        };
}

function serializeVariables(inp) {
  return {
          email: inp.email,
          password: inp.password
        };
}

function makeVariables(email, password, param) {
  return {
          email: email,
          password: password
        };
}

var SignIn_inner = {
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables
};

var include = ApolloClient__React_Hooks_UseMutation.Extend({
      query: query,
      Raw: Raw,
      parse: parse,
      serialize: serialize,
      serializeVariables: serializeVariables
    });

var use = include.use;

var SignIn_useWithVariables = include.useWithVariables;

var SignIn = {
  SignIn_inner: SignIn_inner,
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  use: use,
  useWithVariables: SignIn_useWithVariables
};

var validators = {
  email: undefined,
  password: undefined
};

function initialFieldsStatuses(_input) {
  return {
          email: /* Pristine */0,
          password: /* Pristine */0
        };
}

function initialState(input) {
  return {
          input: input,
          fieldsStatuses: {
            email: /* Pristine */0,
            password: /* Pristine */0
          },
          collectionsStatuses: undefined,
          formStatus: /* Editing */0,
          submissionStatus: /* NeverSubmitted */0
        };
}

function validateForm(input, param, param$1) {
  var match_0 = {
    TAG: /* Ok */0,
    _0: input.email
  };
  var match_0$1 = {
    TAG: /* Ok */0,
    _0: input.password
  };
  var emailResult = match_0;
  var emailResult$1;
  if (emailResult.TAG === /* Ok */0) {
    var passwordResult = match_0$1;
    if (passwordResult.TAG === /* Ok */0) {
      return {
              TAG: /* Valid */0,
              output: {
                email: emailResult._0,
                password: passwordResult._0
              },
              fieldsStatuses: {
                email: /* Dirty */{
                  _0: emailResult,
                  _1: /* Hidden */1
                },
                password: /* Dirty */{
                  _0: passwordResult,
                  _1: /* Hidden */1
                }
              },
              collectionsStatuses: undefined
            };
    }
    emailResult$1 = emailResult;
  } else {
    emailResult$1 = emailResult;
  }
  return {
          TAG: /* Invalid */1,
          fieldsStatuses: {
            email: /* Dirty */{
              _0: emailResult$1,
              _1: /* Hidden */1
            },
            password: /* Dirty */{
              _0: match_0$1,
              _1: /* Hidden */1
            }
          },
          collectionsStatuses: undefined
        };
}

function useForm(initialInput, onSubmit) {
  var memoizedInitialState = React.useMemo((function () {
          return initialState(initialInput);
        }), [initialInput]);
  var match = Formality__ReactUpdate.useReducer(memoizedInitialState, (function (state, action) {
          if (typeof action === "number") {
            switch (action) {
              case /* BlurEmailField */0 :
                  var result = Formality.validateFieldOnBlurWithoutValidator(state.input.email, state.fieldsStatuses.email, (function (status) {
                          var init = state.fieldsStatuses;
                          return {
                                  email: status,
                                  password: init.password
                                };
                        }));
                  if (result !== undefined) {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: state.input,
                              fieldsStatuses: result,
                              collectionsStatuses: state.collectionsStatuses,
                              formStatus: state.formStatus,
                              submissionStatus: state.submissionStatus
                            }
                          };
                  } else {
                    return /* NoUpdate */0;
                  }
              case /* BlurPasswordField */1 :
                  var result$1 = Formality.validateFieldOnBlurWithoutValidator(state.input.password, state.fieldsStatuses.password, (function (status) {
                          var init = state.fieldsStatuses;
                          return {
                                  email: init.email,
                                  password: status
                                };
                        }));
                  if (result$1 !== undefined) {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: state.input,
                              fieldsStatuses: result$1,
                              collectionsStatuses: state.collectionsStatuses,
                              formStatus: state.formStatus,
                              submissionStatus: state.submissionStatus
                            }
                          };
                  } else {
                    return /* NoUpdate */0;
                  }
              case /* Submit */2 :
                  var match = state.formStatus;
                  if (typeof match !== "number" && match.TAG === /* Submitting */0) {
                    return /* NoUpdate */0;
                  }
                  var match$1 = validateForm(state.input, validators, state.fieldsStatuses);
                  if (match$1.TAG !== /* Valid */0) {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: state.input,
                              fieldsStatuses: match$1.fieldsStatuses,
                              collectionsStatuses: match$1.collectionsStatuses,
                              formStatus: /* Editing */0,
                              submissionStatus: /* AttemptedToSubmit */1
                            }
                          };
                  }
                  var output = match$1.output;
                  var error = state.formStatus;
                  var tmp;
                  tmp = typeof error === "number" || error.TAG !== /* SubmissionFailed */1 ? undefined : Caml_option.some(error._0);
                  return {
                          TAG: /* UpdateWithSideEffects */1,
                          _0: {
                            input: state.input,
                            fieldsStatuses: match$1.fieldsStatuses,
                            collectionsStatuses: match$1.collectionsStatuses,
                            formStatus: {
                              TAG: /* Submitting */0,
                              _0: tmp
                            },
                            submissionStatus: /* AttemptedToSubmit */1
                          },
                          _1: (function (param) {
                              var dispatch = param.dispatch;
                              return Curry._2(onSubmit, output, {
                                          notifyOnSuccess: (function (input) {
                                              return Curry._1(dispatch, {
                                                          TAG: /* SetSubmittedStatus */2,
                                                          _0: input
                                                        });
                                            }),
                                          notifyOnFailure: (function (error) {
                                              return Curry._1(dispatch, {
                                                          TAG: /* SetSubmissionFailedStatus */3,
                                                          _0: error
                                                        });
                                            }),
                                          reset: (function (param) {
                                              return Curry._1(dispatch, /* Reset */5);
                                            }),
                                          dismissSubmissionResult: (function (param) {
                                              return Curry._1(dispatch, /* DismissSubmissionResult */4);
                                            })
                                        });
                            })
                        };
                  break;
              case /* DismissSubmissionError */3 :
                  var match$2 = state.formStatus;
                  if (typeof match$2 === "number" || match$2.TAG !== /* SubmissionFailed */1) {
                    return /* NoUpdate */0;
                  } else {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: state.input,
                              fieldsStatuses: state.fieldsStatuses,
                              collectionsStatuses: state.collectionsStatuses,
                              formStatus: /* Editing */0,
                              submissionStatus: state.submissionStatus
                            }
                          };
                  }
              case /* DismissSubmissionResult */4 :
                  var match$3 = state.formStatus;
                  if (typeof match$3 === "number") {
                    if (match$3 === /* Editing */0) {
                      return /* NoUpdate */0;
                    }
                    
                  } else if (match$3.TAG === /* Submitting */0) {
                    return /* NoUpdate */0;
                  }
                  return {
                          TAG: /* Update */0,
                          _0: {
                            input: state.input,
                            fieldsStatuses: state.fieldsStatuses,
                            collectionsStatuses: state.collectionsStatuses,
                            formStatus: /* Editing */0,
                            submissionStatus: state.submissionStatus
                          }
                        };
              case /* Reset */5 :
                  return {
                          TAG: /* Update */0,
                          _0: initialState(initialInput)
                        };
              
            }
          } else {
            switch (action.TAG | 0) {
              case /* UpdateEmailField */0 :
                  var nextInput = Curry._1(action._0, state.input);
                  return {
                          TAG: /* Update */0,
                          _0: {
                            input: nextInput,
                            fieldsStatuses: Formality.validateFieldOnChangeWithoutValidator(nextInput.email, (function (status) {
                                    var init = state.fieldsStatuses;
                                    return {
                                            email: status,
                                            password: init.password
                                          };
                                  })),
                            collectionsStatuses: state.collectionsStatuses,
                            formStatus: state.formStatus,
                            submissionStatus: state.submissionStatus
                          }
                        };
              case /* UpdatePasswordField */1 :
                  var nextInput$1 = Curry._1(action._0, state.input);
                  return {
                          TAG: /* Update */0,
                          _0: {
                            input: nextInput$1,
                            fieldsStatuses: Formality.validateFieldOnChangeWithoutValidator(nextInput$1.password, (function (status) {
                                    var init = state.fieldsStatuses;
                                    return {
                                            email: init.email,
                                            password: status
                                          };
                                  })),
                            collectionsStatuses: state.collectionsStatuses,
                            formStatus: state.formStatus,
                            submissionStatus: state.submissionStatus
                          }
                        };
              case /* SetSubmittedStatus */2 :
                  var input = action._0;
                  if (input !== undefined) {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: input,
                              fieldsStatuses: {
                                email: /* Pristine */0,
                                password: /* Pristine */0
                              },
                              collectionsStatuses: state.collectionsStatuses,
                              formStatus: /* Submitted */1,
                              submissionStatus: state.submissionStatus
                            }
                          };
                  } else {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: state.input,
                              fieldsStatuses: {
                                email: /* Pristine */0,
                                password: /* Pristine */0
                              },
                              collectionsStatuses: state.collectionsStatuses,
                              formStatus: /* Submitted */1,
                              submissionStatus: state.submissionStatus
                            }
                          };
                  }
              case /* SetSubmissionFailedStatus */3 :
                  return {
                          TAG: /* Update */0,
                          _0: {
                            input: state.input,
                            fieldsStatuses: state.fieldsStatuses,
                            collectionsStatuses: state.collectionsStatuses,
                            formStatus: {
                              TAG: /* SubmissionFailed */1,
                              _0: action._0
                            },
                            submissionStatus: state.submissionStatus
                          }
                        };
              case /* MapSubmissionError */4 :
                  var map = action._0;
                  var error$1 = state.formStatus;
                  if (typeof error$1 === "number") {
                    return /* NoUpdate */0;
                  }
                  if (error$1.TAG !== /* Submitting */0) {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: state.input,
                              fieldsStatuses: state.fieldsStatuses,
                              collectionsStatuses: state.collectionsStatuses,
                              formStatus: {
                                TAG: /* SubmissionFailed */1,
                                _0: Curry._1(map, error$1._0)
                              },
                              submissionStatus: state.submissionStatus
                            }
                          };
                  }
                  var error$2 = error$1._0;
                  if (error$2 !== undefined) {
                    return {
                            TAG: /* Update */0,
                            _0: {
                              input: state.input,
                              fieldsStatuses: state.fieldsStatuses,
                              collectionsStatuses: state.collectionsStatuses,
                              formStatus: {
                                TAG: /* Submitting */0,
                                _0: Caml_option.some(Curry._1(map, Caml_option.valFromOption(error$2)))
                              },
                              submissionStatus: state.submissionStatus
                            }
                          };
                  } else {
                    return /* NoUpdate */0;
                  }
              
            }
          }
        }));
  var dispatch = match[1];
  var state = match[0];
  var match$1 = state.formStatus;
  var tmp;
  tmp = typeof match$1 === "number" || match$1.TAG !== /* Submitting */0 ? false : true;
  return {
          updateEmail: (function (nextInputFn, nextValue) {
              return Curry._1(dispatch, {
                          TAG: /* UpdateEmailField */0,
                          _0: (function (__x) {
                              return Curry._2(nextInputFn, __x, nextValue);
                            })
                        });
            }),
          updatePassword: (function (nextInputFn, nextValue) {
              return Curry._1(dispatch, {
                          TAG: /* UpdatePasswordField */1,
                          _0: (function (__x) {
                              return Curry._2(nextInputFn, __x, nextValue);
                            })
                        });
            }),
          blurEmail: (function (param) {
              return Curry._1(dispatch, /* BlurEmailField */0);
            }),
          blurPassword: (function (param) {
              return Curry._1(dispatch, /* BlurPasswordField */1);
            }),
          emailResult: Formality.exposeFieldResult(state.fieldsStatuses.email),
          passwordResult: Formality.exposeFieldResult(state.fieldsStatuses.password),
          input: state.input,
          status: state.formStatus,
          dirty: (function (param) {
              var match = state.fieldsStatuses;
              if (match.email || match.password) {
                return true;
              } else {
                return false;
              }
            }),
          valid: (function (param) {
              var match = validateForm(state.input, validators, state.fieldsStatuses);
              if (match.TAG === /* Valid */0) {
                return true;
              } else {
                return false;
              }
            }),
          submitting: tmp,
          submit: (function (param) {
              return Curry._1(dispatch, /* Submit */2);
            }),
          dismissSubmissionError: (function (param) {
              return Curry._1(dispatch, /* DismissSubmissionError */3);
            }),
          dismissSubmissionResult: (function (param) {
              return Curry._1(dispatch, /* DismissSubmissionResult */4);
            }),
          mapSubmissionError: (function (map) {
              return Curry._1(dispatch, {
                          TAG: /* MapSubmissionError */4,
                          _0: map
                        });
            }),
          reset: (function (param) {
              return Curry._1(dispatch, /* Reset */5);
            })
        };
}

var LoginForm = {
  validators: validators,
  initialFieldsStatuses: initialFieldsStatuses,
  initialCollectionsStatuses: undefined,
  initialState: initialState,
  validateForm: validateForm,
  useForm: useForm
};

var initialState$1 = {
  email: "",
  password: ""
};

function SignIn_View(Props) {
  var match = Curry.app(use, [
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined
      ]);
  var result = match[1];
  var signIn = match[0];
  var form = useForm(initialState$1, (function (param, actions) {
          Request$Peaky.onFinish(Curry._8(signIn, undefined, undefined, undefined, undefined, undefined, undefined, undefined, {
                    email: param.email,
                    password: param.password
                  }), (function (param) {
                  Auth$Peaky.signIn(param.signIn);
                  return Router$Peaky.push(/* Calendar */0);
                }), (function (param) {
                  
                }));
          return Curry._1(actions.notifyOnFailure, undefined);
        }));
  var match$1 = form.input;
  return React.createElement("div", {
              className: "relative w-full min-h-screen flex"
            }, React.createElement(Loader$Peaky.make, {
                  loading: result.loading
                }), React.createElement("div", {
                  className: "bg-white absolute  w-full h-full rounded-bl-full flex justify-center items-center shadow-xl overflow-hidden z-10 opacity-90 ",
                  style: {
                    right: "-20%",
                    top: "-20%"
                  }
                }, React.createElement(Graphic_Login$Peaky.make, {})), React.createElement("div", {
                  className: "bg-green-50 absolute bottom-0 left-0 h-screen flex items-center w-full"
                }, React.createElement("div", {
                      className: "fixed flex flex-col w-1/4 bottom-0 left-0 ml-24 mb-24"
                    }, React.createElement("h1", {
                          className: "text-4xl text-center mb-4 text-green-400 "
                        }, React.createElement(Text$Peaky.make, {
                              children: "Autentykacja"
                            })), React.createElement("form", {
                          onSubmit: (function (e) {
                              e.preventDefault();
                              return Curry._1(form.submit, undefined);
                            })
                        }, React.createElement("div", {
                              className: ""
                            }, React.createElement("div", {
                                  className: "rounded-xl px-8 py-16 border border-gray-100 bg-white  flex flex-col justify-center shadow-lg"
                                }, React.createElement("div", {
                                      className: "pb-8"
                                    }, React.createElement(Input$Peaky.make, {
                                          value: match$1.email,
                                          onChange: (function (email) {
                                              return Curry._2(form.updateEmail, (function (input, value) {
                                                            return {
                                                                    email: value,
                                                                    password: input.password
                                                                  };
                                                          }), email);
                                            }),
                                          placeholder: "E-mail"
                                        })), React.createElement("div", {
                                      className: "pb-8"
                                    }, React.createElement(Input$Peaky.make, {
                                          value: match$1.password,
                                          onChange: (function (password) {
                                              return Curry._2(form.updatePassword, (function (input, value) {
                                                            return {
                                                                    email: input.email,
                                                                    password: value
                                                                  };
                                                          }), password);
                                            }),
                                          placeholder: "Hasło",
                                          type_: "password"
                                        })), React.createElement("div", {
                                      className: "flex justify-center"
                                    }, React.createElement(Button$Peaky.CTA.make, {
                                          htmlType: "submit",
                                          loading: result.loading,
                                          children: React.createElement("span", {
                                                className: "pl-1"
                                              }, React.createElement(Text$Peaky.make, {
                                                    children: "Zaloguj się"
                                                  }))
                                        })), React.createElement("div", {
                                      className: "text-md text-gray-600 text-center mt-8"
                                    }, React.createElement(Text$Peaky.make, {
                                          children: "Zapomniałeś hasła?"
                                        }))))))));
}

var make = SignIn_View;

export {
  SignIn ,
  LoginForm ,
  initialState$1 as initialState,
  make ,
  
}
/* query Not a pure module */
