'use strict';

angular.module('trajectoriesServices', null, null).factory('SolarSystemService', ['BridgeService', function (BridgeService) {

   /* console.log('testing performance...');
    var count = 0;
    var k1 = BridgeService.callSync('loadsolarsystem');
    var t = Date.now() + 1000;

    while(t > Date.now()) {
        var k2 = BridgeService.callSync('solarsystemstate', {et: 1000 * count, center: 399});
        count ++;
    }

    console.log('done: ' + count);*/


    var service = {
        timerange: null,
        bodies: null,
        tree: null,
        init: function () {
            this.timerange = BridgeService.callSync('validtimerange');

            var result = BridgeService.callSync('loadsolarsystem');
            this.bodies = result.bodies;
            this.tree = result.tree;
        },

        getState: function (et, center) {
            console.log('requesting state');
            var state = BridgeService.callSync('solarsystemstate', {et: et, center: center});
            console.log(state);
            return state;
        }
    };

    service.init();

    return service;
}]);
