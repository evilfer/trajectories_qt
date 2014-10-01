'use strict';

describe("Service: MissionManipulator", function () {
  var MissionManipulatorService, emptyMission;

  // define empty mission
  beforeEach(function() {
    emptyMission = {
      metadata: {
        title: 'New mission',
        description: ''
      },
      config: {
      },
      ship: {
        name: 'Ship',
        mass: 1000,
        thrust: 1000,
        isp: 100,
        fuelMass: 2000
      },
      origin: {
        orbit: 399,
        radius: 6521,
        ecc: 1
      },
      plan: []
    };
  });

  // load the controller's module
  beforeEach(module('trajectories'));

  // Initialize the controller and a mock scope
  beforeEach(inject(function (_MissionManipulatorService_) {
    MissionManipulatorService = _MissionManipulatorService_;
  }));

  it('should exist', function () {
    expect(MissionManipulatorService).toBeDefined();
  });

  it('should create empty mission', function() {
    expect(MissionManipulatorService.newMission).toBeDefined();
    expect(MissionManipulatorService.newMission()).toEqual(emptyMission);
  });

  it('should add maneuver', function() {
    MissionManipulatorService.add(emptyMission, 'maneuver');
    expect(emptyMission.plan.length).toBe(1);
    expect(emptyMission.plan[0]).toEqual({
      type: 'maneuver',
      orbit: 0
    });
  });

  it('should add timePeriod', function() {
    MissionManipulatorService.add(emptyMission, 'maneuver');
    MissionManipulatorService.add(emptyMission, 'timePeriod');
    expect(emptyMission.plan.length).toBe(2);
    expect(emptyMission.plan[1]).toEqual({
      type: 'timePeriod',
      period: 0
    });
  });



});
