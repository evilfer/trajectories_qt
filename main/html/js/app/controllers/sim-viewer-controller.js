
angular.module('trajectories', null, null).controller('SimViewerCtrl', function ($scope, SolarSystemService) {

    $scope.center = {
        body: 399
    };

    $scope.date = {
       et: 0
    };

    $scope.solarSystem = {
        center: $scope.center.body,
        bodies: SolarSystemService.bodies,
        tree: SolarSystemService.tree,
        state: null
    };


    var updateCenter = function(center) {
        $scope.solarSystem.state = SolarSystemService.getState(0, center);
        $scope.solarSystem.center = center;
    };

    $scope.$watch('center.body', function() {
       console.log('svc body updated ' + $scope.center.body);
        updateCenter($scope.center.body);
    });


});
