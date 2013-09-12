
App.SimulationMissionStartController = Ember.ObjectController.extend({
  acceptChanges: function() {
    this.get('model').save();
  },
  optionalAttrs: ['inclination', 'latitude', 'longitude'],
  hasInclination: function() {
    return App.Utils.hasAttr(this, 'inclination');
  }.property('inclination'),
  hasLongitude: function() {
    return App.Utils.hasAttr(this, 'longitude');
  }.property('longitude'),
  hasLatitude: function() {
    return App.Utils.hasAttr(this, 'latitude');
  }.property('latitude'),
  showAddButton: function() {
    return App.Utils.optionalAttrAvailable(this);
  }.property('hasInclination', 'hasLongitude', 'hasLatitude')
});


