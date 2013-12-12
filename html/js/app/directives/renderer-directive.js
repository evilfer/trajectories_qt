angular.module('trajectories', null, null).directive('tSimulationRenderer', function () {
    return {
        scope: {
            ngModel: '='
        },

        link: function (scope, element, attrs) {
            console.log(scope.ngModel);

            var renderer = new nspRenderer(element, scope.ngModel);
            renderer.updateScene();
        }
    };
});

