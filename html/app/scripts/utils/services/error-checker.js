'use strict';

/**
 * @ngdoc function
 * @name utils.service:ErrorCheckerService
 * @description
 * # ErrorCheckerService
 * Service of module utils.
 * Checks for errors in data structures.
 */
angular.module('utils').factory('ErrorCheckerService', function () {

  var ErrorCheckerService = function (dataStructure) {
    this.dataStructure = dataStructure;
  };

  ErrorCheckerService.prototype.check = function (data) {
    var errors = {};
    this._checkNode(errors, 'ROOT', data, '_ROOT_');
    return errors;
  };

  ErrorCheckerService.prototype._addError = function (errors, dataPath, error) {
    if (!(dataPath in errors)) {
      errors[dataPath] = [];
    }
    errors[dataPath].push(error);
  };

  ErrorCheckerService.prototype._checkNode = function (errors, dataPath, data, type) {
    var def = this.dataStructure[type];
    switch (def[0]) {
      case 'obj':
        this._checkObj(errors, dataPath, data, def[1]);
    }
  };

  ErrorCheckerService.prototype._checkObj = function (errors, dataPath, data, objDef) {
    if (!data || (typeof data) != 'object' || data instanceof Array) {
      this._addError(errors, dataPath, 'type:obj');
    } else {
      for (var key in objDef) {
        console.log(key, objDef[key]);
        if (objDef.hasOwnProperty(key)) {
          if (objDef[key][0] && !(data[key])) {
            this._addError(errors, dataPath + '.' + key, 'missing');
          }
        }
      }
    }
  };


  return ErrorCheckerService;

});
