# Build

```
npm run build
```

# Watch

```
npm run watch
```

# Firebase

// SINGLE GET
return firebase
        .database()
        .ref("/test/")
        .once("value")
        .then((snapshot) => {
        console.log(snapshot.val());
        return snapshot.val();
        // ...
        });
