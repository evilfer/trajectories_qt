
App.Router.map(function() {
  this.resource('index', {path: '/'});
  this.resource('simulations');
  this.resource('simulation', {path: 'simulation/:table_id'});
});

App.SimulationsRoute = Ember.Route.extend({
  model: function() {
    return App.SimulationMetadata.find();
  }
});
