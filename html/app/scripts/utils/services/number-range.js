'use strict';

/**
 * @ngdoc function
 * @name utils.service:NumberRangeService
 * @description
 * # NumberRangeService
 * Service of module utils.
 * Implements number range type checking and parsing.
 */
angular.module('utils').factory('NumberRangeService', function () {

  var checkStr = function (value) {
      var parts = (value && value.split) ? value.split(':') : [];
      if (parts.length === 3) {
        var a = parseFloat(parts[0]);
        var b = parseFloat(parts[2]);
        var n = parseInt(parts[1]);

        if (isFinite(a) && isFinite(b) && isFinite(n) && n > 0) {
          return false;
        }
      }
      return 'format';
    },
    parseStr = function (value) {
      var parts = value.split(':');
      if (parts.length === 3) {
        var a = parseFloat(parts[0]);
        var b = parseFloat(parts[2]);
        var n = parseInt(parts[1]);
        if (isFinite(a) && isFinite(b) && isFinite(n) && n > 0) {
          var d = b - a;
          if (n > 1 && d !== 0) {
            var g = d / (n - 1);
            var result = [];
            result[0] = a;
            for (var i = 1; i < n - 1; i++) {
              result[i] = a + g * i;
            }
            result[n - 1] = b;
            return result;
          } else {
            return [a];
          }
        }
      }
      return null;
    };

  var NumberRangeService = {
    error: function (value) {
      switch (typeof value) {
        case 'number':
          return false;
        case 'string':
          return checkStr(value);
        default:
          return 'type:numberRange';
      }
    },
    range: function (value) {
      switch (typeof value) {
        case 'number':
          return [value];
        case 'string':
          return parseStr(value);
        default:
          return null;
      }
    }
  };


  return NumberRangeService;

});
