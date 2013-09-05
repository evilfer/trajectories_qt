
App.Simulation = DS.Model.extend({
  metadata: DS.belongsTo('App.SimulationMetadata'),
  config: DS.belongsTo('App.SimulationConfiguration'),
  ship: DS.belongsTo('App.Ship'),
  mission: DS.belongsTo('App.Mission')
});
