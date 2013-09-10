
App.Simulation = DS.Model.extend({
  metadata: DS.belongsTo('simulation_metadata'),
  config: DS.belongsTo('simulation_configuration'),
  ship: DS.belongsTo('ship'),
  mission: DS.belongsTo('mission')
});
