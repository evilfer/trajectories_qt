/*global window, Ember, QtCppJsBridge */

(function() {
  window.Bridge = {};

  Bridge.Ops = {
    FIND: 0,
    FINDALL: 1,
    CREATE: 2,
    UPDATE: 3,
    DELETE: 4
  };

  Bridge.Comm = {
    opId: 0,
    ops: {},
    enabled: false,
    init: function() {
      if (typeof QtCppJsBridge !== 'undefined') {
        this.enabled = true;
        QtCppJsBridge.call_js.connect(Bridge.Comm.call_js);
      }
    },
    call_js: function(op, complete, answer) {
      var opData = this.ops[op];
      if (opData) {
        opData.adapter.invoked(opData.store, opData.request, opData.localRecord, answer);
        if (complete) {
          delete this.ops[op];
        }
      }
    },
    call_qt: function(op, adapter, store, data, localRecord) {
      var id = this.opId;
      this.opId++;
      this.ops[id] = {
        adapter: adapter,
        store: store,
        request: data,
        localRecord: localRecord ? localRecord : null
      };
      
      QtCppJsBridge.call_qt(op, data);
    }
  };




  var get = Ember.get, fmt = Ember.String.fmt,
          dump = Ember.get(window, 'JSON.stringify') || function(object) {
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
    fixturesForType: function(type) {
      if (type.FIXTURES) {
        var fixtures = Ember.A(type.FIXTURES);
        return fixtures.map(function(fixture) {
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
    queryFixtures: function(fixtures, query, type) {
      Ember.assert('Not implemented: You must override the DS.FixtureAdapter::queryFixtures method to support querying the fixture store.');
    },
    updateFixtures: function(type, fixture) {
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
    mockJSON: function(type, record) {
      return this.serialize(record, {includeId: true});
    },
    /*
     Adapter methods
     */
    generateIdForRecord: function(store, record) {
      return Ember.guidFor(record);
    },
    find: function(store, type, id) {

      var fixtures = this.fixturesForType(type),
              fixture;

      Ember.warn("Unable to find fixtures for model type " + type.toString(), fixtures);

      if (fixtures) {
        fixture = Ember.A(fixtures).findProperty('id', id);
      }

      if (fixture) {
        this.simulateRemoteCall(function() {
          this.didFindRecord(store, type, fixture, id);
        }, this);
      }
    },
    findMany: function(store, type, ids) {
      var fixtures = this.fixturesForType(type);

      Ember.assert("Unable to find fixtures for model type " + type.toString(), !!fixtures);

      if (fixtures) {
        fixtures = fixtures.filter(function(item) {
          return ids.indexOf(item.id) !== -1;
        });
      }

      if (fixtures) {
        this.simulateRemoteCall(function() {
          this.didFindMany(store, type, fixtures);
        }, this);
      }
    },
    findAll: function(store, type) {
      var fixtures = this.fixturesForType(type);

      Ember.assert("Unable to find fixtures for model type " + type.toString(), !!fixtures);

      this.simulateRemoteCall(function() {
        this.didFindAll(store, type, fixtures);
      }, this);
    },
    findQuery: function(store, type, query, array) {
      var fixtures = this.fixturesForType(type);

      Ember.assert("Unable to find fixtures for model type " + type.toString(), !!fixtures);

      fixtures = this.queryFixtures(fixtures, query, type);

      if (fixtures) {
        this.simulateRemoteCall(function() {
          this.didFindQuery(store, type, fixtures, array);
        }, this);
      }
    },
    createRecord: function(store, type, record) {
      var fixture = this.mockJSON(type, record);

      this.updateFixtures(type, fixture);

      this.simulateRemoteCall(function() {
        this.didCreateRecord(store, type, record, fixture);
      }, this);
    },
    updateRecord: function(store, type, record) {
      var data = this.mockJSON(type, record);
      Bridge.Comm.call_qt({op: Bridge.Ops.UPDATE, type: type, record: data});

      this.updateFixtures(type, data);
      
    },
    deleteRecord: function(store, type, record) {

    },
    /*
     @listener
     */
    invoked: function(store, request, data, localRecord) {
      switch (request.op) {
        case Bridge.Ops.FIND:
          this.didFindRecord(store, request.type, data, request.id);
          break;
        case Bridge.Ops.FINDALL:
          this.didFindAll(store, request.type, data);
          break;
        case Bridge.Ops.CREATE:
          this.didCreateRecord(store, request.type, localRecord, data);
          break;
        case Bridge.Ops.UPDATE:
          this.didUpdateRecord(store, request.type, localRecord, data);
          break;
        case Bridge.Ops.DELETE:
          this.didDeleteRecord(store, request.type, localRecord);
          break;
      }
    }

  });

  Bridge.Comm.init();

})();

