let fromObject = data => Obj.magic(data);

let toList: (Firebase.Database.DataSnapshot.t, string) => 'a = [%raw
  {| function toArray(s, userId) {
    const data = s.val();
    console.log(data);
    if(data) {
      return Object.keys(data).reduce((acc, x) => acc.concat({ ...data[x], id: x }), []).filter(x => x.doctorId === userId);
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
