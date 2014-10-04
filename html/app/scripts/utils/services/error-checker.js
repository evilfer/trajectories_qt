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

  var ErrorCheckerService = function (dataStructure, extend) {
    this.dataStructure = dataStructure;
    this._methods = {
      'obj': '_checkObj',
      'number': '_checkNumber',
      'string': '_checkString',
      'array': '_checkArray'
    };

    this._extend = extend || {};
  };

  ErrorCheckerService.prototype.check = function (data) {
    var errors = {};
    this._checkNode(errors, '', data, '_ROOT_');
    return errors;
  };

  ErrorCheckerService.prototype._addError = function (errors, dataPath, error) {
    if (!(dataPath in errors)) {
      errors[dataPath] = [];
    }
    errors[dataPath].push(error);
  };

  ErrorCheckerService.prototype._appendPath = function (base, path) {
    return base.length > 0 ? (base + '.' + path) : path;
  };

  ErrorCheckerService.prototype._checkNode = function (errors, dataPath, data, type) {
    var def = this.dataStructure[type];

    var typeName = def[0];
    var typeOptions = def.length > 1 ? def[1] : {};
    if (typeName in this._methods) {
      this[this._methods[typeName]](errors, dataPath, data, typeOptions);
    } else if (typeName in this._extend) {
      var error = this._extend[typeName](data);
      if (error) {
        this._addError(errors, dataPath, error);
      }
    }
  };

  ErrorCheckerService.prototype._checkObj = function (errors, dataPath, data, objDef) {
    if (!data || (typeof data) != 'object' || data instanceof Array) {
      this._addError(errors, dataPath, 'type:obj');
    } else {
      for (var key in objDef) {
        if (objDef.hasOwnProperty(key)) {
          if (objDef[key][0] && !(key in data)) {
            this._addError(errors, this._appendPath(dataPath, key), 'missing');
          }
        }
      }

      for (key in data) {
        if (data.hasOwnProperty(key)) {
          if (key in objDef) {
            var typeName = objDef[key][1];
            this._checkNode(errors, this._appendPath(dataPath, key), data[key], typeName);
          } else {
            this._addError(errors, this._appendPath(dataPath, key), 'notallowed');
          }
        }
      }
    }
  };

  ErrorCheckerService.prototype._checkNumber = function (errors, dataPath, data, objDef) {
    if ((typeof data) != 'number') {
      this._addError(errors, dataPath, 'type:number');
    }
  };

  ErrorCheckerService.prototype._checkString = function (errors, dataPath, data, objDef) {
    if ((typeof data) != 'string') {
      this._addError(errors, dataPath, 'type:string');
    }
  };

  ErrorCheckerService.prototype._checkArray = function (errors, dataPath, data, objDef) {
    if (!data || (typeof data) != 'object' || !(data instanceof Array)) {
      this._addError(errors, dataPath, 'type:array');
    } else {
      for (var i = 0; i < data.length; i++) {
        var item = data[i];

        if (objDef.typeKey) {
          if (item == null) {
            this._addError(errors, this._appendPath(dataPath, i), 'nullitem');
          } else if ((typeof item) != 'object' || item instanceof Array) {
            this._addError(errors, this._appendPath(dataPath, i), 'type:obj');
          } else if (!(objDef.typeKey in item)) {
            this._addError(errors, this._appendPath(dataPath, i), 'missingtype');
          } else {
            var arrayItemType = item[objDef.typeKey];
            if (!(arrayItemType in objDef.types)) {
              this._addError(errors, this._appendPath(dataPath, i), 'badtype');
            } else {
              var itemType = objDef.types[arrayItemType];
              this._checkNode(errors, this._appendPath(dataPath, i), item, itemType);
            }
          }
        }
      }
    }
  };


  return ErrorCheckerService;

});
