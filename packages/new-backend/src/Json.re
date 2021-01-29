let fromObject = data => Obj.magic(data);

let toList: (Firebase.Database.DataSnapshot.t, string) => 'a = [%raw
  {| function toArray(s, userId) {
    const a = s.val();
    return Object.keys(a).reduce((acc, x) => acc.concat({ ...a[x], id: x }), []).filter(x => x.doctorId === userId);
  }
|}
];
