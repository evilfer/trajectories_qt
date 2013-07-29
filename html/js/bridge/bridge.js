/*global QtCppJsBridge */

(function () {
    window.Bridge = Ember.Namespace.create();

    Bridge.Comm = {
        enabled: false,
        init: function () {
            if (typeof QtCppJsBridge !== 'undefined') {
                this.enabled = true;
                QtCppJsBridge.call_js.connect(Bridge.Comm.call_js);
            }
        },
        call_js: function () {
            alert('js called!');
        },
        call_qt: function () {
            console.log('call qt!');
            QtCppJsBridge.call_qt();
        }
    };

    Bridge.Comm.init();


    var get = Ember.get, fmt = Ember.String.fmt,
        dump = Ember.get(window, 'JSON.stringify') || function (object) {
            return object.toString();
        };

    /**
     `Bridge.BridgeAdapter` is an extension of `DS.FixtureAdapter` to ease
     the transition from fixtures to backend stored/modified models.

     It's created by copying the code of Fixture Adapter and adapt it to
     communicate with the Qt backend.


     @class BridgeAdapter
     @constructor
     @namespace Bridge
     @extends DS.Adapter
     */
    Bridge.BridgeAdapter = DS.Adapter.extend({

        serializer: DS.FixtureSerializer,

        /*
         Implement this method in order to provide data associated with a type
         */
        fixturesForType: function (type) {
            if (type.FIXTURES) {
                var fixtures = Ember.A(type.FIXTURES);
                return fixtures.map(function (fixture) {
                    var fixtureIdType = typeof fixture.id;
                    if (fixtureIdType !== "number" && fixtureIdType !== "string") {
                        throw new Error(fmt('the id property must be defined as a number or string for fixture %@', [dump(fixture)]));
                    }
                    fixture.id = fixture.id + '';
                    return fixture;
                });
            }
            return null;
        },

        /*
         Implement this method in order to query fixtures data
         */
        queryFixtures: function (fixtures, query, type) {
            Ember.assert('Not implemented: You must override the DS.FixtureAdapter::queryFixtures method to support querying the fixture store.');
        },

        updateFixtures: function (type, fixture) {
            if (!type.FIXTURES) {
                type.FIXTURES = [];
            }

            var fixtures = type.FIXTURES;

            this.deleteLoadedFixture(type, fixture);

            fixtures.push(fixture);
        },

        /*
         Implement this method in order to provide provide json for CRUD methods
         */
        mockJSON: function (type, record) {
            return this.serialize(record, { includeId: true });
        },

        /*
         Adapter methods
         */
        generateIdForRecord: function (store, record) {
            return Ember.guidFor(record);
        },

        find: function (store, type, id) {
            var fixtures = this.fixturesForType(type),
                fixture;

            Ember.warn("Unable to find fixtures for model type " + type.toString(), fixtures);

            if (fixtures) {
                fixture = Ember.A(fixtures).findProperty('id', id);
            }

            if (fixture) {
                this.simulateRemoteCall(function () {
                    this.didFindRecord(store, type, fixture, id);
                }, this);
            }
        },

        findMany: function (store, type, ids) {
            var fixtures = this.fixturesForType(type);

            Ember.assert("Unable to find fixtures for model type " + type.toString(), !!fixtures);

            if (fixtures) {
                fixtures = fixtures.filter(function (item) {
                    return ids.indexOf(item.id) !== -1;
                });
            }

            if (fixtures) {
                this.simulateRemoteCall(function () {
                    this.didFindMany(store, type, fixtures);
                }, this);
            }
        },

        findAll: function (store, type) {
            var fixtures = this.fixturesForType(type);

            Ember.assert("Unable to find fixtures for model type " + type.toString(), !!fixtures);

            this.simulateRemoteCall(function () {
                this.didFindAll(store, type, fixtures);
            }, this);
        },

        findQuery: function (store, type, query, array) {
            var fixtures = this.fixturesForType(type);

            Ember.assert("Unable to find fixtures for model type " + type.toString(), !!fixtures);

            fixtures = this.queryFixtures(fixtures, query, type);

            if (fixtures) {
                this.simulateRemoteCall(function () {
                    this.didFindQuery(store, type, fixtures, array);
                }, this);
            }
        },

        createRecord: function (store, type, record) {
            var fixture = this.mockJSON(type, record);

            this.updateFixtures(type, fixture);

            this.simulateRemoteCall(function () {
                this.didCreateRecord(store, type, record, fixture);
            }, this);
        },

        updateRecord: function (store, type, record) {
            var fixture = this.mockJSON(type, record);

            this.updateFixtures(type, fixture);

            this.simulateRemoteCall(function () {
                this.didUpdateRecord(store, type, record, fixture);
            }, this);
        },

        deleteRecord: function (store, type, record) {
            var fixture = this.mockJSON(type, record);

            this.deleteLoadedFixture(type, fixture);

            this.simulateRemoteCall(function () {
                this.didDeleteRecord(store, type, record);
            }, this);
        },

        /*
         @private
         */
        deleteLoadedFixture: function (type, record) {
            var existingFixture = this.findExistingFixture(type, record);

            if (existingFixture) {
                var index = type.FIXTURES.indexOf(existingFixture);
                type.FIXTURES.splice(index, 1);
                return true;
            }
        },

        findExistingFixture: function (type, record) {
            var fixtures = this.fixturesForType(type);
            var id = this.extractId(type, record);

            return this.findFixtureById(fixtures, id);
        },

        findFixtureById: function (fixtures, id) {
            return Ember.A(fixtures).find(function (r) {
                if ('' + get(r, 'id') === '' + id) {
                    return true;
                } else {
                    return false;
                }
            });
        },

        simulateRemoteCall: function (callback, context) {
            Ember.run.once(context, callback);
        }
    });

})();

