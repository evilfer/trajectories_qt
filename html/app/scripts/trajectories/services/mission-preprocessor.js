'use strict';

/**
 * @ngdoc function
 * @name trajectories.service:MissionPreprocessorService
 * @description
 * # MissionPreprocessorService
 * Service of module trajectories.
 * Prepares mission for simulator.
 */
angular.module('trajectories').service('MissionPreprocessorService', ['NumberRangeService',
  function (NumberRangeService) {

    this._stepTypes = {
      timePeriod: [
        ['period', 'numberRange']
      ],
      maneuver: [
        ['orbit', 'number'],
        ['prograde', 'numberRange'],
        ['offplane', 'numberRange'],
        ['outward', 'numberRange']
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
      var type = this._stepTypes[step.type];
      var fixed = {type: step.type}, ranges = [];

      for (var i = 0; i < type.length; i++) {
        var attr = type[i][0];
        var attrType = type[i][1];

        if (attrType === 'numberRange') {
          var range = attr in step ? NumberRangeService.range(step[attr]) : [0];
          ranges.push({attr: attr, range: range});
        } else {
          fixed[attr] = attr in step ? step[attr] :
            (attrType === 'number' ? 0 : '');
        }
      }

      var options = [];
      iterateRanges({}, ranges, 0, fixed, options);
      return options;
    }
  }]);
