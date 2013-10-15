'use strict';

/* Controllers */


function TestCtrl($scope, Bridge) {
    var result = Bridge.callQt("test", {});
    $scope.test = result.test;
}

//TestCtlr.$inject = ['$scope', 'Bridge'];

