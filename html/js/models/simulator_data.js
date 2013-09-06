
App.SimulatorData = DS.Model.extend({
  simulation: DS.belongsTo('simulation'),
  viewdate: DS.belongsTo('solar_system_state')
});

