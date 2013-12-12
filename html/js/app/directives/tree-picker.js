angular.module('trajectories', null, null).directive('tTreePicker', function () {
    return {
        scope: {
            ngModel: '='
        },

        link: function ($scope, element, attrs) {
            var $element = angular.element(element);

            var bodyName = function(id) {
                return $scope.ngModel.bodies[id].name;
            };

            var isActive = function(id) {
                return id === $scope.center;
            };

            var appendChildren = function($container, children) {
                var $ul = $('<ul></ul>');
                for (var id in children) {
                    var $li = $('<li></li>');
                    $li.append(bodyName(id));
                    var childsChildren = children[id];
                    if (childsChildren) {
                        appendChildren($li, childsChildren);
                    }
                    $ul.append($li);
                }
                $container.append($ul);
            };

            appendChildren($element, $scope.ngModel.tree);
        }
    };
});

