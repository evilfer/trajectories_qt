
App.SimulationMetadata = DS.Model.extend({
  title: DS.attr('string'),
  description: DS.attr('string'),
  author: DS.attr('string'),
  modified: DS.attr('date')
});
methods = {};