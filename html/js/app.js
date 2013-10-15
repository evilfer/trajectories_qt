'use strict';

/* App Module */

angular.module('trajectories', ['trajectoriesServices']).
  config(['$routeProvider', function($routeProvider) {
  $routeProvider.
      when('/test', {templateUrl: 'partials/test.html',   controller: TestCtrl}).
      otherwise({redirectTo: '/test'});
}]);
