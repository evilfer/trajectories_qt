/*global QtCppJsBridge*/

'use strict';

angular.module('trajectoriesServices', null, null).factory('BridgeService', function() {

    var ready = typeof QtCppJsBridge !== 'undefined';

    var bridge = {
        ready: ready,
        /**
         *
         * @param {string} op
         * @param {*=} data
         * @returns {*}
         */
        callSync: function(op, data) {
            console.log(op);
            console.log(data);

            var result = QtCppJsBridge.call_qt_sync(op, data || {});
            console.log(result);

            return result;
        }
    };

    return bridge;
});
