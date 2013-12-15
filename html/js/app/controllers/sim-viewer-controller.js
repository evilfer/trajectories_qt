
angular.module('trajectories', null, null).controller('SimViewerCtrl', function ($scope, SolarSystemService) {

    var center = 301;

    $scope.solarSystem = {
        center: center,
        bodies: SolarSystemService.bodies,
        tree: SolarSystemService.tree,
        state: SolarSystemService.getState(0, center)
    };

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
