

App.MissionStart = DS.Model.extend({
  mission: DS.belongsTo('mission'),
  date: DS.attr('number'),
  planet: DS.attr('string'),
  radius: DS.attr('number'),
  inclination: DS.attr('number'),
  longitude: DS.attr('number'),
  latitude: DS.attr('number')
});


