'use strict';

/* App Module */

angular.module('trajectories', ['trajectoriesServices', 'ui.router'], null).config([
    '$stateProvider',
    '$urlRouterProvider',
    function ($stateProvider, $urlRouterProvider) {
        $stateProvider
            .state('home', {
                url: '/home',
                templateUrl: 'partials/home.html'
            })
            .state('list', {
                url: '/list',
                templateUrl: 'partials/list.html',
                controller: 'ListCtrl'
            })
            .state('sim', {
                url: '/sim:simId',
                templateUrl: 'partials/sim.html',
                controller: 'SimCtrl'
            });

        $urlRouterProvider.otherwise('/home');
    }
]);
