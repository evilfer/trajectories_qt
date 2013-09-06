
App.SimulationMetadata = DS.Model.extend({
  simulation: DS.belongsTo('simulation'),
  title: DS.attr('string'),
  description: DS.attr('string'),
  author: DS.attr('string'),
  modified: DS.attr('string')
});
