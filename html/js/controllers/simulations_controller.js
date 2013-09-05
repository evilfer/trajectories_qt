
App.SimulationsController = Ember.ArrayController.extend({
  newSimulation: function() {
    var sim = App.Simulation.createRecord({
    });

    var metadata = App.SimulationMetadata.createRecord({
      title: 'new',
      description: '',
      author: '',
      modified: 0
    });

    sim.set('metadata', metadata);
    metadata.set('simulation', sim);


    var config = App.SimulationConfiguration.createRecord({
      ephemerides: 'cspice'
    });

    sim.set('config', config);
    config.set('simulation', sim);

    var ship = App.Ship.createRecord({
      name: "ship",
      mass: 1000,
      thrust: 1000,
      isp: 100,
      fuelmass: 1000
    });

    sim.set('ship', ship);
    ship.set('simulation', sim);

    var mission = App.Mission.createRecord({
    });

    sim.set('mission', mission);
    mission.set('simulation', sim);

    var start = App.MissionStart.createRecord({
      date: 0,
    });
    
    start.set('mission', mission);
    mission.set('start', start);
    
    sim.save();
    metadata.save();
    config.save();
    ship.save();
    mission.save();
    start.save();
  }
});

