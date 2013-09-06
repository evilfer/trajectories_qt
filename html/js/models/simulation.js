
App.Simulation = DS.Model.extend({
  metadata: DS.belongsTo('simulationMetadata'),
  config: DS.belongsTo('simulationConfiguration'),
  ship: DS.belongsTo('ship'),
  mission: DS.belongsTo('mission')
});
