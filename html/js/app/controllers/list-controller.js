


angular.module('trajectories', null, null).controller('ListCtrl', function ($scope, $state, DocumentsService) {
    $scope.list = DocumentsService.list();

    $scope.actions = {
        newSim: function() {
            var newId = DocumentsService.createNew();
            $state.go('sim', {simId: newId});
        }
    }
});
