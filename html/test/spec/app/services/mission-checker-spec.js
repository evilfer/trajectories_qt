'use strict';

describe("Service: MissionChecker", function () {
  var MissionManipulatorService, MissionCheckerService, mission;

  // load the controller's module
  beforeEach(module('trajectories'));

  // Initialize the controller and a mock scope
  beforeEach(inject(function (_MissionManipulatorService_, _MissionCheckerService_) {
    MissionManipulatorService = _MissionManipulatorService_;
    MissionCheckerService = _MissionCheckerService_;
  }));

  beforeEach(function() {
    mission = MissionManipulatorService.newMission();
  });

  it('should pass new mission', function () {
    expect(MissionCheckerService.check(mission)).toEqual({});
  });
});
