
App.Router.map(function() {
  this.resource('index', {path: '/'});
  this.resource('simulations');
  this.resource('simulator', function() {
    this.resource('simulation', {path: '/simulation/:simulation_id'}, function() {
      this.route('config');
      this.route('ship');
      this.route('mission');
    });
  });
});

App.SimulationsRoute = Ember.Route.extend({
  model: function() {
    return this.get('store').find('simulation');
  }
});

App.SimulatorRoute = Ember.Route.extend({
  model: function() {
    return this.get('store').find('simulator_data', 'singleton');
  }
});

App.SimulationIndexRoute = Ember.Route.extend({
  model: function() {
    var data = this.modelFor('simulator');
    var simulation = this.modelFor('simulation');
    if (data.get('simulation') != simulation) {
      data.set('simulation', simulation);
      data.save();
    }
    return simulation.get('metadata');
  }
});

App.SimulationConfigRoute = Ember.Route.extend({
  model: function() {
    return this.modelFor('simulation').get('config');
  }
});

App.SimulationShipRoute = Ember.Route.extend({
  model: function() {
    return this.modelFor('simulation').get('ship');
  }
});

App.SimulationMissionRoute = Ember.Route.extend({
  model: function() {
    return this.modelFor('simulation').get('mission');
  }
});
