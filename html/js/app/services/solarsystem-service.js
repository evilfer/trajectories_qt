'use strict';

angular.module('trajectoriesServices', null, null).factory('SolarSystemService', ['BridgeService', function (BridgeService) {

    var service = {
        timerange: null,
        bodies: null,
        tree: null,
        init: function () {
            this._timerange = BridgeService.callSync('validtimerange');

            var result = BridgeService.callSync('loadsolarsystem');
            this._bodies = result.bodies;
            this._tree = result.tree;
        },

        getState: function (et) {
            return BridgeService.callSync('solarsystemstate', {et: et});
        }
    };

    service.init();

    return service;
}]);
