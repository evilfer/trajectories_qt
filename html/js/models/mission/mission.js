

App.Mission = DS.Model.extend({
  simulation: DS.belongsTo('simulation'),
  start: DS.belongsTo('missionStart'),
  duration: DS.attr('number')
  //events: DS.hasMany('App.MissionEvent', {polymorphic: true})
});


