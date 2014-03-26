angular.module('trajectories', null, null).directive('tDateInput', function () {
    return {
        templateUrl: 'partials/date-input.html',

        scope: {
            ngModel: '='
        },

        controller: function($scope) {
            $scope.view = {
              main: 'front'
            };
            $scope.dateConverter = new tDate($scope.ngModel);
        },

        link: function (scope, element, attrs) {
        }
    };
});

