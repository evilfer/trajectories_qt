angular.module('trajectories', null, null).directive('tTreePicker', function () {
    return {
        scope: {
            ngModel: '='
        },

        link: function ($scope, element, attrs) {

            var $element = angular.element(element);

            var appendChildren = function($container, children, level, parentPos, parentLevelSize) {
                var hasSelectedChildren = false;
                var $div = $('<div></div>').addClass('tree-children');
                var hide = level > 0;

                var count = 0;

                for (var id in children) {
                    count ++;
                }

                var i = 0;
                for (var id in children) {
                    var isSelected = id == $scope.ngModel.selection;
                    var $div2 = $('<div></div>').addClass('tree-item');


                    if (hide) {
                        $div2.addClass('tree-hide');
                    }

                    $div2.append($('<div></div>').addClass('tree-item-name').html(children[id].label).attr('item-id', id).click(function() {
                        $scope.selected($(this).attr('item-id'));
                    }));
                    var iconDiv = $('<div></div>').addClass('tree-item-icon').appendTo($div2);

                    var childsChildren = children[id].children;

                    if (childsChildren) {
                        iconDiv.addClass('has-children');
                        var isParentOfSelected = appendChildren($div2, childsChildren, level + 1, i, count);
                    }

                    if (isSelected) {
                        $div2.addClass('tree-selected');
                        hasSelectedChildren = true;
                    } else if (isParentOfSelected) {
                        hasSelectedChildren = true;
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

            $scope.selected = function(id) {
                $scope.$apply(function() {
                    $scope.ngModel.selection = id;
                });
            };

            $scope.$watch('ngModel.selection', function(newVal, oldVal) {
                update();
            });
        }
    };
});

