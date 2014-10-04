'use strict';

describe("Service: NumberRange", function () {
  var NumberRangeService;

  // load the controller's module
  beforeEach(module('utils'));

  beforeEach(inject(function (_NumberRangeService_) {
    NumberRangeService = _NumberRangeService_;
  }));


  it('should exist', function () {
    expect(NumberRangeService).toBeDefined();
  });

  it('should detect bad types', function() {
    expect(NumberRangeService.error({})).toBe('type:numberRange');
    expect(NumberRangeService.error([])).toBe('type:numberRange');
  });

  it('should accept number', function() {
    expect(NumberRangeService.error(0)).toBeFalsy();
    expect(NumberRangeService.error(1.4)).toBeFalsy();
  });

  describe('bad strings', function() {
    var t = function(v) {
      it('should detect "' + v + '" as bad format', function () {
        expect(NumberRangeService.error(v)).toBe('format');
      });
    };

    t('k');
    t('1:2:');
    t('1:2');
    t('1:a:3');
    t('1::3');
    t('1:0:3');
    t('1:-1:3');
  });

  it('should accept strings', function() {
    expect(NumberRangeService.error("1:1:1")).toBeFalsy();
    expect(NumberRangeService.error("1.4:2:5.4")).toBeFalsy();
  });

  it ('should retrieve correct range', function() {
    var e = function(v, r) {
      expect(NumberRangeService.range(v)).toEqual(r);
    };

    e({}, null);
    e([], null);
    e(0, [0]);
    e(1.4, [1.4]);
    e("1:1:1", [1]);
    e("1:2:1", [1]);
    e("1:2:2", [1, 2]);
    e("1:5:2", [1, 1.25, 1.5, 1.75, 2]);
    e("1.25:5:2.25", [1.25, 1.5, 1.75, 2, 2.25]);
  });
});
