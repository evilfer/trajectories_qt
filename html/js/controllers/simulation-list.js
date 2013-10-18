'use strict';

function SimulationListCtrl($scope, TrajectoriesData) {
  var result = TrajectoriesData.getList();
  $scope.list = result.list;

  $scope.actions = {
    createSimulation: function() {
      var result = TrajectoriesData.createSimulation();
      $scope.list = result.list;
    }
  };
}

//SimulationListCtrl.$inject = ['$scope', 'TrajectoriesData'];

