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
      types: {}
    }]
  };

  this._errorChecker = new ErrorCheckerService(this._structure);

  this.check = function (mission) {
    return this._errorChecker.check(mission);
  };

}]);
