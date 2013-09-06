
App.Ship = DS.Model.extend({
  simulation: DS.belongsTo('simulation'),
  name: DS.attr('string'),
  mass: DS.attr('number'),
  thrust: DS.attr('number'),
  isp: DS.attr('number'),
  fuelmass: DS.attr('number')
});
