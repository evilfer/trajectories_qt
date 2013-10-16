'use strict';

function SimulationListCtrl($scope, Bridge) {
    var result = Bridge.callQt("simulation_list");
    $scope.list = result.list;
}

//SimulationListCtrl.$inject = ['$scope', 'Bridge'];

