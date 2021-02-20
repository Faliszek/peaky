


function handleError(feedbackOpt, err) {
  var feedback = feedbackOpt !== undefined ? feedbackOpt : "";
  console.log("We should handle this error:\n\n" + feedback, err);
  
}

export {
  handleError ,
  
}
/* No side effect */
