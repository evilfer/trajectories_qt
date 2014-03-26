angular.module('trajectories', null, null).directive('tBodyPicker', function (SolarSystemService) {
    return {
        templateUrl: 'partials/body-picker.html',

        scope: {
            ngModel: '='
        },

        link: function (scope, element, attrs) {
            var buildTree = function(inParent) {
                var outParent = {};
                for (var inChild in inParent) {
                    var outChild = {
                        id: inChild,
                        label: SolarSystemService.bodies[inChild].name,
                        children: inParent[inChild] ? buildTree(inParent[inChild]) : false
                    };
                    outParent[inChild] = outChild;
                }
                return outParent;
            };

            scope.treeModel = {
                tree: buildTree(SolarSystemService.tree),
                selection: scope.ngModel.body
            };

            scope.isOpen = false;

            scope.openTree = function() {
                scope.isOpen = ! scope.isOpen;
            };

            scope.centerName = function() {
                return SolarSystemService.bodies[scope.treeModel.selection].name;
            };

            scope.$watch('treeModel.selection', function() {
                scope.ngModel.body = scope.treeModel.selection;
            });
        }
    };
});

