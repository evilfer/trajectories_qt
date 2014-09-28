'use strict';

describe("Service: MissionManager", function () {
  var MissionManagerService, emptyMission;

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
        mass: '1000',
        thrust: '1000',
        isp: '100',
        fuelMass: '2000'
      },
      origin: {
        orbit: '399',
        radius: '6521',
        ecc: '1'
      },
      plan: []
    };
  });

  // load the controller's module
  beforeEach(module('trajectories'));

  // Initialize the controller and a mock scope
  beforeEach(inject(function (_MissionManagerService_) {
    MissionManagerService = _MissionManagerService_;
  }));

  it('should exist', function () {
    expect(MissionManagerService).toBeDefined();
  });

  it('should create empty mission', function() {
    expect(MissionManagerService.newMission).toBeDefined();
    expect(MissionManagerService.newMission()).toEqual(emptyMission);
  });

});
