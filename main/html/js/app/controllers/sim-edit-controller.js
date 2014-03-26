
angular.module('trajectories', null, null).controller('SimEditCtrl', function ($scope, DocumentsService) {

    $scope.view = {
        tab: 'title',
        open: function(tab) {
            this.tab = tab;
        },
        isOpen: function(tab) {
            return this.tab === tab;
        }
    };

});
