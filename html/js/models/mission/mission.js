

App.Mission = DS.Model.extend({
  simulation: DS.belongsTo('App.Simulation'),
  start: DS.belongsTo('App.MissionStart'),
  duration: DS.attr('number')
  //events: DS.hasMany('App.MissionEvent', {polymorphic: true})
});


