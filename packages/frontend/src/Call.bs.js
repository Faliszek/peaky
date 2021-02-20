


function fromGraphql(id, duration, timestamp, answered, withWho, param) {
  return {
          id: id,
          duration: duration,
          timestamp: timestamp,
          answered: answered,
          withWho: withWho
        };
}

export {
  fromGraphql ,
  
}
/* No side effect */
