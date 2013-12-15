angular.module('trajectories', null, null).directive('tTreePicker', function () {
    return {
        scope: {
            ngModel: '='
        },

        link: function ($scope, element, attrs) {

            console.log($scope.ngModel);

            var $element = angular.element(element);


            var levelHide = [false, false, true];

            var appendChildren = function($container, children, level, parentPos, parentLevelSize) {
                var hasSelectedChildren = false;
                var $div = $('<div></div>').addClass('tree-children');
                var hide = levelHide[level];

                var count = 0;

                for (var id in children) {
                    count ++;
                }

                var i = 0;
                for (var id in children) {
                    var isSelected = id == $scope.ngModel.center;
                    console.log(id + ' ' + $scope.ngModel.center + ' ' + isSelected);

                    var $div2 = $('<div></div>').addClass('tree-item');


                    if (hide) {
                        $div2.addClass('tree-hide');
                    }

                    $div2.append($('<div></div>').addClass('tree-item-name').html($scope.ngModel.bodies[id].name));
                    var childsChildren = children[id];

                    if (childsChildren) {
                        var isParentOfSelected = appendChildren($div2, childsChildren, level + 1, i, count);
                    }

                    if (isSelected) {
                        $div2.addClass('tree-selected');
                        hasSelectedChildren = true;
                    } else if (isParentOfSelected) {
                        $div2.addClass('tree-parent-of-selected');
                    }


                    $div.append($div2);

                    i++;
                }

                var delta = (1 - count) / 2;
                if (parentPos + delta + count > parentLevelSize) {
                    delta = parentLevelSize - count - parentPos;
                }
                if (delta < -parentPos) {
                    delta = -parentPos;
                }

                $div.css({'top': (delta * 100) + '%'});

                $container.append($div);

                return hasSelectedChildren;
            };

            var update = function() {
                $element.html('');
                appendChildren($element, $scope.ngModel.tree, 0, 0, 1);
            };


            var isActive = function(id) {
                return id === $scope.center;
            };

            update();
        }
    };
});

