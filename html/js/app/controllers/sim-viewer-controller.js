
angular.module('trajectories', null, null).controller('SimViewerCtrl', function ($scope, SolarSystemService) {

    $scope.solarSystem = {
        center: 399,
        bodies: SolarSystemService.bodies,
        tree: SolarSystemService.tree,
        state: SolarSystemService.getState(0)
    };

    console.log($scope.solarSystem);

    $scope.bodyName = function(id) {
        return $scope.solarSystem.bodies[id].name;
    };

    $scope.centerName = function() {
        return $scope.bodyName($scope.solarSystem.center);
    };

    $scope.pickerOpen = true;

    $scope.chooseCenter = function() {
        $scope.pickerOpen = !$scope.pickerOpen;
    };

});
