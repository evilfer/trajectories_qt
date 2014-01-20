'use strict';

angular.module('trajectoriesServices', null, null).factory('DocumentsService', ['BridgeService', function (BridgeService) {

    var defaultShip = {name: "ship", mass: 1000, thrust: 1000, isp: 100, fuelmass: 1000};

    var documents = {
        docs: null,
        status: null,
        init: function () {
            var result = BridgeService.callSync('list');
            if (typeof result['documents'] !== 'undefined') {
                this.docs = result['documents'];
            } else {
                this.docs = {};
            }

            this.status = {};

            for (var idStr in this.docs) {
                this.status[idStr] = {
                    stored: true,
                    modified: false,
                    detailed: false
                };
            }
        },


        list: function () {
            return this.docs;
        },


        /**
         *
         * @param id
         * @returns {*}
         */
        get: function (id) {
            if (typeof this.docs[id] === 'undefined') {
                return null;
            }

            if (!this.status[id].detailed) {
                var result = BridgeService.callSync('load', {id: id});
                if (result['ok']) {
                    this.docs[id] = result['document'];
                    this.status[id].detailed = true;
                    this.status[id].modified = false;
                } else {
                    delete this.docs[id];
                    delete this.status[id];
                }
            }

            return this.docs[id];
        },

        getStatus: function(id) {
            return this.status[id];
        },

        /**
         *
         * @returns {string}
         */
        createNew: function () {
            var intId = 1;
            for (var idStr in this.docs) {
                var id = parseInt(idStr);
                if (id >= intId) {
                    intId = id + 1;
                }
            }

            var newId = intId.toString();

            this.docs[newId] = {
                config: {},
                metadata: {},
                ship: tClone(defaultShip),
                mission: {}
            };

            this.status[newId] = {
                stored: false,
                modified: true,
                detailed: true
            };

            return newId.toString();
        },
        /**
         *
         * @param {string} id
         * @returns {boolean}
         */
        save: function (id) {
            if (typeof this.docs[id] === 'undefined' || !this.status[id].detailed || !this.status[id].modified) {
                return false;
            }

            var result = BridgeService.callSync("save", {
                id: id,
                document: JSON.stringify(this.docs[id])
            });

            if (result['ok']) {
                this.status[id].modified = false;
                return true;
            } else {
                return false;
            }
        }
    };

    documents.init();

    return documents;
}]);
