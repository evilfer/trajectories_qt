angular.module('trajectories', null, null).directive('tSimulationRenderer', function () {
    return {
        scope: {
            ngModel: '='
        },

        link: function (scope, element, attrs) {
            console.log('renderer directive');
            console.log(scope.ngModel);
            var renderer = new tRenderer(element, scope.ngModel);

            scope.$watch('ngModel.center', function() {
                console.log('rd ' + scope.ngModel.center);
                renderer.updateScene();
            });
        }
    };
});

