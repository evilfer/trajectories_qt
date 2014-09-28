'use strict';

/**
 * @ngdoc overview
 * @name trajectories
 * @description
 * # trajectoriesApp
 *
 * Main module of the application.
 */
angular.module('trajectories', [
  'ngAnimate',
  'ngCookies',
  'ngResource',
  'ngRoute',
  'ngSanitize',
  'ngTouch',
  'utils'
]).config(function ($routeProvider) {
  $routeProvider
    .when('/', {
      templateUrl: '../../views/main.html',
      controller: 'MainCtrl'
    })
    .when('/about', {
      templateUrl: '../../views/about.html',
      controller: 'AboutCtrl'
    })
    .otherwise({
      redirectTo: '/'
    });
});
