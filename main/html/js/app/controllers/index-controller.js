

angular.module('trajectories', null, null).controller('IndexCtrl', function ($scope, BridgeService) {
    $scope.bridgeReady = BridgeService.ready;
});