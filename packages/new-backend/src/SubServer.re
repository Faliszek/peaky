%raw
{|
  const { execute, subscribe } = require('graphql');
  const { createServer } = require('http');
  const { SubscriptionServer } = require('subscriptions-transport-ws');
|};

let start = [%bs.raw
  {|




function(app, schema) {
  const ws = createServer(app);

ws.listen(4001, () => {
  // Set up the WebSocket for handling GraphQL subscriptions.
  new SubscriptionServer(
    {
      execute,
      subscribe,
      schema,
    },
    {
      server: ws,
      path: '/subscriptions',
    },
  );
});
}
|}
];
