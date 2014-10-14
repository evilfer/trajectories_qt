'use strict';

/**
 * @ngdoc function
 * @name trajectories.service:MissionPreprocessorService
 * @description
 * # MissionPreprocessorService
 * Service of module trajectories.
 * Prepares mission for simulator.
 */
angular.module('trajectories').service('MissionPreprocessorService', ['NumberRangeService', function (NumberRangeService) {
  this._stepTypes = {
    timePeriod: [
      ['period', 'numberRange']
    ],
    maneuver: [
      ['orbit', 'number'],
      ['prograde', 'numberRange'],
      ['offplane', 'numberRange'],
      ['outward', 'numberRange']
    ],
    origin: [
      ['orbit', 'number'],
      ['radius', 'number'],
      ['ecc', 'number']
    ]
  };

  var createOption = function (obj, fixed, options) {
    options.push(jQuery.extend({}, fixed, obj));
  };

  var iterateRanges = function (obj, ranges, level, fixed, options) {
    if (level < ranges.length) {
      var rangeDef = ranges[level];
      for (var i = 0; i < rangeDef.range.length; i++) {
        obj[rangeDef.attr] = rangeDef.range[i];
        iterateRanges(obj, ranges, level + 1, fixed, options);
      }
    } else {
      createOption(obj, fixed, options);
    }
  };

  this._stepOptions = function (step) {
    return this._itemOptions(step, step.type, true);
  };


  this._itemOptions = function (item, typeName, includeType) {
    var type = this._stepTypes[typeName];
    var ranges = [],
      fixed = includeType ? {type: typeName} : {};

    for (var i = 0; i < type.length; i++) {
      var attr = type[i][0];
      var attrType = type[i][1];

      if (attrType === 'numberRange') {
        var range = attr in item ? NumberRangeService.range(item[attr]) : [0];
        ranges.push({attr: attr, range: range});
      } else {
        fixed[attr] = attr in item ? item[attr] :
          (attrType === 'number' ? 0 : '');
      }
    }

    var options = [];
    iterateRanges({}, ranges, 0, fixed, options);
    return options;
  };

  this.tree = function (mission) {
    var plan = this._itemOptions(mission.origin, 'origin');

    var steps = mission.plan.map(this._stepOptions, this);

    var append = function (item, itemIndex, childIndex, parentId) {
      item.id = parentId ? parentId + '.' + itemIndex : itemIndex.toString();

      if (childIndex < steps.length) {
        item.children = steps[childIndex].map(function (option, optionIndex) {
          var o = jQuery.extend({}, option);
          append(o, optionIndex, childIndex + 1, item.id);
          return o;
        });
      }
    };

    plan.forEach(function(origin, index) {
      append(origin, index, 0, null);
    });

    return plan;
  };
}]);
