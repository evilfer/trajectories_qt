'use strict';

describe("Service: ErrorChecker", function () {
  var ErrorCheckerService,
    errorChecker;

  // load the controller's module
  beforeEach(module('utils'));

  beforeEach(inject(function (_ErrorCheckerService_) {
    ErrorCheckerService = _ErrorCheckerService_;
  }));

  describe('Empty definition', function () {

    // Initialize the controller and a mock scope
    beforeEach(function () {
      errorChecker = new ErrorCheckerService({
        '_ROOT_': ['obj', {}]
      });
    });

    it('should exist', function () {
      expect(errorChecker).toBeDefined();
    });

    it('should detect non obj root', function () {
      var dataItems = [null, 4, [1, 2], "e"];
      var result = {
        ROOT: ['type:obj']
      };

      for (var i = 0; i < dataItems.length; i++) {
        expect(errorChecker.check(dataItems[i])).toEqual(result);
      }

      expect(errorChecker.check({})).toEqual({});
    });
  });

  describe('ROOT obj definition', function () {

    // Initialize the controller and a mock scope
    beforeEach(function () {
      errorChecker = new ErrorCheckerService({
        '_ROOT_': ['obj', {
          'a': [true, 'n'],
          'b': [true, 'n'],
          'c': [false, 'n']
        }],
        'n': ['number']
      });
    });

    it('should detect missing obj children', function () {
      expect(errorChecker.check({})).toEqual({
        'ROOT.a': ['missing'],
        'ROOT.b': ['missing']
      });

      expect(errorChecker.check({a: 1})).toEqual({
        'ROOT.b': ['missing']
      });

      expect(errorChecker.check({a: 1, b: 2})).toEqual({});
    });
  });

});
