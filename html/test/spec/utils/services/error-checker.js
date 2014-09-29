'use strict';

describe("Service: ErrorChecker", function () {
  var ErrorCheckerService;

  // load the controller's module
  beforeEach(module('utils'));

  beforeEach(inject(function (_ErrorCheckerService_) {
    ErrorCheckerService = _ErrorCheckerService_;
  }));

  describe('Empty definition', function () {
    var errorChecker;

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
        root: ['type:obj']
      };

      for (var i = 0; i < dataItems.length; i++) {
        expect(errorChecker.check(dataItems[i])).toEqual(result);
      }

      expect(errorChecker.check({})).toEqual({});
    });
  });


  describe('ROOT obj definition', function () {
    var errorChecker;

    // Initialize the controller and a mock scope
    beforeEach(function () {
      errorChecker = new ErrorCheckerService({
        '_ROOT_': ['obj', {
          'a': [true, 'N'],
          'b': [true, 'N'],
          'c': [false, 'N']
        }],
        'N': ['number']
      });
    });

    it('should detect missing obj children', function () {
      expect(errorChecker.check({})).toEqual({
        'root.a': ['missing'],
        'root.b': ['missing']
      });

      expect(errorChecker.check({a: 1})).toEqual({
        'root.b': ['missing']
      });

      expect(errorChecker.check({a: 1, b: 2})).toEqual({});
    });

    it('should detect children not allowed', function () {
      expect(errorChecker.check({a: 1, b: 2, d: null})).toEqual({
        'root.d': ['notallowed']
      });
    });

  });


  describe('number/string checking', function () {
    var errorChecker;

    beforeEach(function () {
      errorChecker = new ErrorCheckerService({
        '_ROOT_': ['obj', {
          'a': [false, 'N'],
          'b': [false, 'S']
        }],
        'N': ['number'],
        'S': ['string']
      });
    });

    it('should detect null values', function () {
      expect(errorChecker.check({a: null})).toEqual({
        'root.a': ['type:number']
      });
    });

    it('should detect bad strings', function () {
      expect(errorChecker.check({b: 4})).toEqual({
        'root.b': ['type:string']
      });
    });

    it('should pass 0 numbers and empty strings', function () {
      expect(errorChecker.check({a: 0, b: ''})).toEqual({});
    });
  });

  describe('array checking', function () {
    var errorChecker;

    beforeEach(function () {
      errorChecker = new ErrorCheckerService({
        '_ROOT_': ['obj', {
          'a': [false, 'A']
        }],
        'A': ['array', {
          typeKey: 'type',
          types: {'c_obj': 'C_OBJ'}
        }],
        'STR': ['string'],
        'NUM': ['number'],
        'C_OBJ': ['obj', {
          'cs': [false, 'STR'],
          'cn': [false, 'NUM'],
          'type': [false, 'STR']
        }]
      });
    });

    it('should detect array property with bad type', function() {
      expect(errorChecker.check({a: 0})).toEqual({
        'root.a': ['type:array']
      });

      expect(errorChecker.check({a: null})).toEqual({
        'root.a': ['type:array']
      });

      expect(errorChecker.check({a: []})).toEqual({});
    });

    it('should detect object array null elements', function() {
      expect(errorChecker.check({
        a:[null]
      })).toEqual({
        'root.a.0': ['nullitem']
      });
    });

    it('should detect object array non-object elements', function() {
      expect(errorChecker.check({
        a:[0]
      })).toEqual({
        'root.a.0': ['type:obj']
      });
    });

    it('should detect object array items without type', function() {
      expect(errorChecker.check({
        a:[{}]
      })).toEqual({
        'root.a.0': ['missingtype']
      });
    });

    it('should detect object array items with bad type', function() {
      expect(errorChecker.check({
        a:[{type: 'k'}]
      })).toEqual({
        'root.a.0': ['badtype']
      });
    });

    it('should pass good object array', function() {
      expect(errorChecker.check({
        a:[{type: 'c_obj'}]
      })).toEqual({});
    });

    it('should check object array items', function() {
      expect(errorChecker.check({
        a:[
          {type: 'c_obj'},
          {type: 'c_obj', 'cs': '', 'cn': 0},
          {type: 'c_obj', 'cs': 0, 'cn': ''}
        ]
      })).toEqual({
        'root.a.2.cs': ['type:string'],
        'root.a.2.cn': ['type:number']
      });
    });
  });
});
