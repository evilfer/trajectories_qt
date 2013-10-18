
'use strict';

angular.module('trajectoriesBridgeServices', []).factory('Bridge', function() {
    var bridge = {
        callQt: function(op, data) {
            return QtCppJsBridge.call_qt(op, data || {});
        }
    };
    return bridge;
});
