
App.SimulationConfiguration = DS.Model.extend({
  simulation: DS.belongsTo('App.Simulation'),
  ephemerides: DS.attr('string')
});

