'use strict';

function SimulationCtrl($scope, TrajectoriesData) {
  $scope.view = {
    currentMenuOption: 'metadata',
    setMenuOption: function(option) {
      this.currentMenuOption = option;
    }
  };
  
  $scope.simulation = TrajectoriesData.getSimulation("1");
  $scope.$watch('simulation', function(newValue) {
    TrajectoriesData.change($scope.simulation.metadata.id);
  }, true);
}

//SimulationListCtrl.$inject = ['$scope', 'TrajectoriesData'];

