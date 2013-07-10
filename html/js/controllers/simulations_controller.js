
App.SimulationsController = Ember.ArrayController.extend({
  newSimulation: function() {
    var sim = App.SimulationMetadata.createRecord({
      title: 'new',
      description: '',
      author: '',
      modified: 0
    });
    sim.save();
  }
});

