'use strict';


function fromObject(data) {
  return data;
}

var toOwnedList = (function toArray(s, userId, owner) {
    const data = s.val();
    const fieldToCompare = owner === "doctor" ? "doctorId" : "patientId";

    if(data) {
      return Object.keys(data).reduce((acc, x) => acc.concat({ ...data[x], id: x }), []).filter(x => x[fieldToCompare] === userId);
    } else {
      return []
    }
  });

var toList = (function toArray(s) {
    const data = s.val();
    if(data) {
      return Object.keys(data).reduce((acc, x) => acc.concat({ ...data[x], id: x }), []);
    } else {
      return []
    }
  });

var toCallsList = (function toArray(s, users) {
    const calls = toList(s);
      console.log(calls, users);
      if(calls) {
      return calls.reduce((acc, c) => {
          return acc.concat({
            id: c.id,
            answered: c.answered,
            duration: c.duration,
            timestamp: c.timestamp,
            from_: users.find(u => u.id == c.fromId),
            to_: users.find(u => u.id == c.toId),
            })
      }, []);
      } else {
        return []
      }
  });

var toObject = (function toObject(obj, id) {
    return {...obj.val(), id};
  });

exports.fromObject = fromObject;
exports.toOwnedList = toOwnedList;
exports.toList = toList;
exports.toCallsList = toCallsList;
exports.toObject = toObject;
/* No side effect */
