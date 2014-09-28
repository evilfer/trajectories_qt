'use strict';

/**
 * @ngdoc function
 * @name trajectories.service:MissionManagerService
 * @description
 * # MissionManagerService
 * Service of module trajectories.
 * Instantiates missions and manipulate their structure.
 */
angular.module('trajectories').service('MissionManagerService', function () {

  this.newMission = function() {
    return {
      metadata: {
        title: 'New mission',
        description: ''
      },
      config: {
      },
      ship: {
        name: 'Ship',
        mass: '1000',
        thrust: '1000',
        isp: '100',
        fuelMass: '2000'
      },
      origin: {
        orbit: '399',
        radius: '6521',
        ecc: '1'
      },
      plan: []
    };
  };



});
