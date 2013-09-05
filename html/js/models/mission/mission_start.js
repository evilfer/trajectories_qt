

App.MissionStart = DS.Model.extend({
  mission: DS.belongsTo('App.Mission'),
  date: DS.attr('number')
});


