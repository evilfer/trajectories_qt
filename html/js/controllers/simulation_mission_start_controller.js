
App.SimulationMissionStartController = App.ObjectVariableParamsController.extend({
  acceptChanges: function() {
    this.get('model').save();
  },
  optionalAttrs: [
    {key: 'inclination', label: 'Inclination'},
    {key: 'latitude', label: 'Latitude'},
    {key: 'longitude', label: 'Longitude'}
  ],
  hasInclination: function() {
    console.log(this._hasAttr('inclination'));
    return this._hasAttr('inclination');
  }.property('inclination'),
  hasLongitude: function() {
    return this._hasAttr('longitude');
  }.property('longitude'),
  hasLatitude: function() {
    return this._hasAttr('latitude');
  }.property('latitude'),
  availableAttr: function() {
    return this._availableOptionalAttrs();
  }.property('hasInclination', 'hasLongitude', 'hasLatitude'),
  showAddButton: function() {
    return this._hasAvailableOptionalAttrs();
  }.property('availableAttr')

});
