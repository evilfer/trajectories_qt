
App.Ship = DS.Model.extend({
  simulation: DS.belongsTo('App.Simulation'),
  name: DS.attr('string'),
  mass: DS.attr('number'),
  thrust: DS.attr('number'),
  isp: DS.attr('number'),
  fuelmass: DS.attr('number')
});
