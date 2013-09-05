
App.SimulatorData = DS.Model.extend({
  simulation: DS.belongsTo('App.Simulation'),
  viewdate: DS.belongsTo('App.SolarSystemState')
});

