
 
App.SimulationsController = Ember.ArrayController.extend({
  _createRecord: function(type, params, then) {
    var record = this.get('store').createRecord(type, params);

    record.save().then(function(record_) {
      if (then) {
        then(record);
      }
    });
  },
  _linkRecords: function(a, propA, b, propB, then) {
    a.set(propA, b);
    a.save().then(function(a_) {
      b.set(propB, a_);
      b.save().then(function(b_) {
        if (then)
          then(a_, b_);
      });
    });
  },
  _linkRecords2: function(a, propA, b, propB) {
    a.set(propA, b);
    b.set(propB, a);
  },
  _saveRecords: function() {
    for (var i = 0; i < arguments.length; i++) {
      arguments[i].save().then(function(record) {
        record.updateRecordArrays();
      });
    }
  },
  newSimulation: function() {
    var controller = this;

    controller._createRecord('simulation', {}, function(sim0) {
      controller._createRecord('simulation_metadata', {title: 'new', description: '', author: '', modified: ''}, function(metadata0) {
        controller._createRecord('simulation_configuration', {ephemerides: 'cspice'}, function(config0) {
          controller._createRecord('ship', {name: "ship", mass: 1000, thrust: 1000, isp: 100, fuelmass: 1000}, function(ship0) {
            controller._createRecord('mission', {}, function(mission0) {
              controller._createRecord('mission_start', {date: 0}, function(start0) {

                controller._linkRecords2(sim0, 'metadata', metadata0, 'simulation');
                controller._linkRecords2(sim0, 'config', config0, 'simulation');
                controller._linkRecords2(sim0, 'ship', ship0, 'simulation');
                controller._linkRecords2(sim0, 'mission', mission0, 'simulation');
                controller._linkRecords2(mission0, 'start', start0, 'mission');

                controller._saveRecords(sim0, metadata0, config0, ship0, mission0, start0);
                /*
                 controller._linkRecords(sim0, 'metadata', metadata0, 'simulation', function(sim1, metadata1) {
                 controller._linkRecords(sim1, 'config', config0, 'simulation', function(sim2, config1) {
                 controller._linkRecords(sim2, 'ship', ship0, 'simulation', function(sim3, ship1) {
                 controller._linkRecords(sim3, 'mission', mission0, 'simulation', function(sim4, mission1) {
                 controller._linkRecords(mission1, 'start', start0, 'mission');
                 });
                 });
                 });
                 });*/
              })
            });
          });
        });
      });
    });
  }
});

