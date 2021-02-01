let fromObject = data => Obj.magic(data);

let toList: (Firebase.Database.DataSnapshot.t, string) => 'a = [%raw
  {| function toArray(s, userId) {
    const data = s.val();
    if(data) {
      return Object.keys(data).reduce((acc, x) => acc.concat({ ...data[x], id: x }), []).filter(x => x.doctorId === userId);
    } else {
      return []
    }
  }
|}
];

let toUserList: Firebase.Database.DataSnapshot.t => 'a = [%raw
  {| function toArray(s) {
    const data = s.val();
    if(data) {
      return Object.keys(data).reduce((acc, x) => acc.concat({ ...data[x], id: x }), []);
    } else {
      return []
    }
  }
|}
];

let toCallsList:
  (Firebase.Database.DataSnapshot.t, array(Domain.User.t)) => 'a = [%raw
  {| function toArray(s, users) {
    const calls = toUserList(s);
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
  }
|}
];

let toObject: (Firebase.Database.DataSnapshot.t, string) => 'a = [%raw
  {| function toObject(obj, id) {
    return {...obj.val(), id};
  }
|}
];
