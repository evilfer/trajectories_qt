

App.MissionStart = DS.Model.extend({
  mission: DS.belongsTo('mission'),
  date: DS.attr('number')
});


