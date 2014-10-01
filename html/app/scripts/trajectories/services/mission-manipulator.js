'use strict';

/**
 * @ngdoc function
 * @name trajectories.service:MissionManipulatorService
 * @description
 * # MissionManipulatorService
 * Service of module trajectories.
 * Instantiates missions and manipulate their structure.
 */
angular.module('trajectories').service('MissionManipulatorService', function () {

  this._items = {
    'maneuver': {orbit: 0},
    'timePeriod': {period: 0}
  };

  this.newMission = function () {
    return {
      metadata: {
        title: 'New mission',
        description: ''
      },
      config: {
      },
      ship: {
        name: 'Ship',
        mass: 1000,
        thrust: 1000,
        isp: 100,
        fuelMass: 2000
      },
      origin: {
        orbit: 399,
        radius: 6521,
        ecc: 1
      },
      plan: []
    };
  };

  this.add = function (mission, type) {
    mission.plan.push(jQuery.extend(true, {type: type}, this._items[type]));
  };

});
