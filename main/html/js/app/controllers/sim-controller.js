

angular.module('trajectories', null, null).controller('SimCtrl', function ($scope, $state, DocumentsService) {
    $scope.id = $state.params['simId'];

    $scope.simulation = DocumentsService.get($scope.id);
    $scope.status = DocumentsService.getStatus($scope.id);

    $scope.actions = {
        save: function() {
          DocumentsService.save($scope.id);
        },
        close: function() {
            $state.go('list');
        }
    };

    $scope.edit = {
        tab: 'title',
        open: function(tab) {
            this.tab = tab;
        },
        isOpen: function(tab) {
            return this.tab === tab;
        }
    };

});
