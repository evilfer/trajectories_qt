'use strict';

/* App Module */

angular.module('trajectories', ['trajectoriesServices']).
  config(['$routeProvider', function($routeProvider) {
  $routeProvider.
      when('/welcome', {templateUrl: 'partials/welcome.html'}).
      when('/simulations', {templateUrl: 'partials/simulations.html', controller: SimulationListCtrl}).
      when('/simulations/:simId', {templateUrl: 'partials/simulation.html', controller: SimulationCtrl}).
      otherwise({redirectTo: '/welcome'});
}]);
