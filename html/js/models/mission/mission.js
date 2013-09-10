

App.Mission = DS.Model.extend({
  simulation: DS.belongsTo('simulation'),
  start: DS.belongsTo('mission_start'),
  duration: DS.attr('number')
  //events: DS.hasMany('App.MissionEvent', {polymorphic: true})
});


