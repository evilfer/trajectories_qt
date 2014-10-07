'use strict';

/**
 * @ngdoc function
 * @name trajectories.service:MissionCheckerService
 * @description
 * # MissionCheckerService
 * Service of module trajectories.
 * Checks the validity of mission documents.
 */
angular.module('trajectories').service('MissionCheckerService', ['ErrorCheckerService', function (ErrorCheckerService) {

  this._structure = {
    'STR': ['string'],
    'NUM': ['number'],
    'RANGE': ['numberRange'],
    '_ROOT_': ['obj', {
      'metadata': [true, 'METADATA'],
      'ship': [true, 'SHIP'],
      'config': [true, 'CONFIG'],
      'origin': [true, 'ORIGIN'],
      'plan': [true, 'PLAN']
    }],
    'METADATA': ['obj', {
      'title': [true, 'STR'],
      'description': [true, 'STR']
    }],
    'CONFIG': ['obj', {}],
    'SHIP': ['obj', {
      'name': [true, 'STR'],
      'mass': [true, 'NUM'],
      'thrust': [true, 'NUM'],
      'isp': [true, 'NUM'],
      'fuelMass': [true, 'NUM']
    }],
    'ORIGIN': ['obj', {
      orbit: [true, 'NUM'],
      radius: [true, 'NUM'],
      ecc: [true, 'NUM']
    }],
    'PLAN': ['array', {
      typeKey: 'type',
      types: {
        'timePeriod': 'STEP_TIMEPERIOD',
        'maneuver': 'STEP_MANEUVER'
      }
    }],
    'STEP_TIMEPERIOD': ['obj', {
      type: [true, 'STR'],
      period: [true, 'RANGE']
    }],
    'STEP_MANEUVER': ['obj', {
      type: [true, 'STR'],
      orbit: [true, 'NUM'],
      prograde: [false, 'RANGE'],
      offplane: [false, 'RANGE'],
      outward: [false, 'RANGE']
    }]
  };


  this._errorChecker = new ErrorCheckerService(this._structure);

  this.check = function (mission) {
    return this._errorChecker.check(mission);
  };

}]);
