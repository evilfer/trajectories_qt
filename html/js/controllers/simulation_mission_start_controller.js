
App.SimulationMissionStartController = Ember.ObjectController.extend({
  acceptChanges: function() {
    this.get('model').save();
  }
});


