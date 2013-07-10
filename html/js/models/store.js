
App.Adapter = DS.FixtureAdapter.extend({
});

App.Store = DS.Store.extend({
  adapter: App.Adapter
});
