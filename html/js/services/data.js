


'use strict';

angular.module('trajectoriesDataServices', ['trajectoriesBridgeServices']).factory('TrajectoriesData', function(Bridge) {
  var data = {
    simulations: {},
    getList: function() {
      return Bridge.callQt("simulation_list");
    },
    getSimulation: function(id) {
      if (!this.simulations[id]) {
        var result = Bridge.callQt("get_simulation", {id: id});
        this.simulations[id] = result.simulation;
      }
      return this.simulations[id];
    },
    change: function(id) {
      Bridge.callQt("save_simulation", this.simulations[id]);
    },
    createSimulation: function() {
      return Bridge.callQt("create_simulation");
    }
  };
  
  return data;
});
