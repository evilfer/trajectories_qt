'use strict';

describe("Service: MissionPreprocessor", function () {
  var MissionPreprocessorService;

  // load the controller's module
  beforeEach(module('trajectories'));

  // Initialize the controller and a mock scope
  beforeEach(inject(function (_MissionPreprocessorService_) {
    MissionPreprocessorService = _MissionPreprocessorService_;
  }));

  it('should be defined', function () {
    expect(MissionPreprocessorService).toBeDefined();
  });


  describe('mission processing', function () {
    var MissionManipulatorService, mission;

    beforeEach(inject(function (_MissionManipulatorService_) {
      MissionManipulatorService = _MissionManipulatorService_;
    }));

    beforeEach(function () {
      mission = MissionManipulatorService.newMission();
      MissionManipulatorService.add(mission, 'timePeriod');
      MissionManipulatorService.add(mission, 'maneuver');
    });

    it('should create one timePeriod option', function () {
      var options = MissionPreprocessorService._stepOptions(mission.plan[0]);
      expect(options.length).toBe(1);
      expect(options).toEqual([{type: 'timePeriod', period: 0}]);
    });

    it('should create two timePeriod options', function () {
      mission.plan[0].period = "0:2:1";
      var options = MissionPreprocessorService._stepOptions(mission.plan[0]);

      expect(options.length).toBe(2);
      expect(options).toEqual([
        {type: 'timePeriod', period: 0},
        {type: 'timePeriod', period: 1}
      ]);
    });

    it('should create one maneuver option', function () {
      var options = MissionPreprocessorService._stepOptions(mission.plan[1]);

      expect(options.length).toBe(1);
      expect(options).toEqual([
        {type: 'maneuver', orbit: 0, prograde: 0, offplane: 0, outward: 0}
      ]);
    });

    it('should create two maneuver options', function () {
      mission.plan[1].prograde = "0:2:1";
      var options = MissionPreprocessorService._stepOptions(mission.plan[1]);

      expect(options.length).toBe(2);
      expect(options).toEqual([
        {type: 'maneuver', orbit: 0, prograde: 0, offplane: 0, outward: 0},
        {type: 'maneuver', orbit: 0, prograde: 1, offplane: 0, outward: 0}
      ]);
    });

    it('should create four maneuver options', function () {
      mission.plan[1].prograde = "0:2:1";
      mission.plan[1].offplane = "3:2:4";
      var options = MissionPreprocessorService._stepOptions(mission.plan[1]);

      expect(options.length).toBe(4);
      expect(options).toEqual([
        {type: 'maneuver', orbit: 0, prograde: 0, offplane: 3, outward: 0},
        {type: 'maneuver', orbit: 0, prograde: 0, offplane: 4, outward: 0},
        {type: 'maneuver', orbit: 0, prograde: 1, offplane: 3, outward: 0},
        {type: 'maneuver', orbit: 0, prograde: 1, offplane: 4, outward: 0}
      ]);
    });

  });
});
