
App.Router.map(function() {
  this.resource('index', {path: '/'});
  this.resource('simulations');
  this.resource('simulation', {path: 'simulation/:simulation_id'}, function() {
    this.route('config');
    this.route('ship');
    this.route('mission');
  });
});

App.SimulationsRoute = Ember.Route.extend({
  model: function() {
    return App.Simulation.find();
  }
});

App.SimulationRoute = Ember.Route.extend({
  model: function(params) {
    return App.Simulation.find(params.simulation_id);
  }
});

App.SimulationIndexRoute = Ember.Route.extend({
  model: function() {
    return this.modelFor('simulation').get('metadata');
  }
});
