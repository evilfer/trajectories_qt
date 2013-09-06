
App.SimulationConfiguration = DS.Model.extend({
  simulation: DS.belongsTo('simulation'),
  ephemerides: DS.attr('string')
});

