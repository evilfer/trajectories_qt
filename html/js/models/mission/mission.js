

App.Mission = DS.Model.extend({
  simulation: DS.belongsTo('App.Simulation'),
  start: DS.belongsTo('App.StartEvent'),
  duration: DS.attr('number'),
  events: DS.hasMany('App.MissionEvent', {polymorphic: true})
});


