
App.SimulationsController = Ember.ArrayController.extend({
  newSimulation: function() {
    var metadata = App.SimulationMetadata.createRecord({
      title: 'new',
      description: '',
      author: '',
      modified: 0
    });
    metadata.save();

    var sim = App.Simulation.createRecord({
    });
    sim.save();
    
    sim.set('metadata', metadata);
    metadata.set('simulation', sim);
    
    sim.save();
    metadata.save();
  }
});

