
App.SimulationIndexController = Ember.ObjectController.extend({
  acceptChanges: function() {
    this.get('model').save();
  }
});

