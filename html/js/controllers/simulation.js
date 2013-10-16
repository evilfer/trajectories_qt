'use strict';

function SimulationCtrl($scope, Bridge) {
  var result = Bridge.callQt("get_simulation", {id: "1"});

  $scope.currentMenuOption = 'metadata';
  $scope.setMenuOption = function(option) {
    this.currentMenuOption = option;
  };

  $scope.ok = result.ok;
  $scope.simulation = result.simulation;
  $scope.simulation.metadata.__defineGetter__("superid", function() {
    return 'id!';
  });
}

//SimulationListCtrl.$inject = ['$scope', 'Bridge'];

