/*global window, Ember, QtCppJsBridge */

(function() {
  window.Bridge = {};

  Bridge.Ops = {
    FIND: 0,
    FINDALL: 1,
    CREATE: 2,
    UPDATE: 3,
    DELETE: 4,
    NEWID: 5
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
    call_js: function(opId, complete, answer) {
      Bridge.Comm.processJsCall(opId, complete, answer);
    },
    processJsCall: function(opId, complete, answer) {
      var opData = this.ops[opId];
      if (opData) {
        opData.adapter.invoked(opData.op, opData.adapter, opData.store, opData.type, opData.request, answer, opData.localRecord);
        if (complete) {
          delete this.ops[opId];
        }
      }
    },
    call_qt: function(op, adapter, store, type, data, localRecord) {
      var id = this.opId;
      this.opId++;
      this.ops[id] = {
        op: op,
        adapter: adapter,
        store: store,
        type: type,
        request: data,
        localRecord: localRecord ? localRecord : null
      };

      QtCppJsBridge.call_qt(op, id, data);
    },
    call_qt_sync: function(op, data) {
      return QtCppJsBridge.call_qt_sync(op, data);
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
    serializer: DS.JSONSerializer,
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
    globalObjectType: function(localType) {
      var typeString = localType.toString();
      var parts = typeString.split(".");
      var name = parts[parts.length - 1];
      return name.replace(/([A-Z])/g, '_$1').toLowerCase().slice(1);
    },
    /*
     Adapter methods
     */
    generateIdForRecord: function(store, record) {
      var type = this.globalObjectType(record.constructor);
      var answer = Bridge.Comm.call_qt_sync(Bridge.Ops.NEWID, {type: type});
      return answer.id;
    },
    find: function(store, type, id) {
      Bridge.Comm.call_qt(Bridge.Ops.FIND, this, store, type, {
        type: this.globalObjectType(type),
        id: id
      });
    },
    findMany: function(store, type, ids) {
      Ember.assert("find many not implemented", true);
    },
    findAll: function(store, type) {
      Bridge.Comm.call_qt(Bridge.Ops.FINDALL, this, store, type, {
        type: this.globalObjectType(type)
      });
    },
    findQuery: function(store, type, query, array) {
      Ember.assert("find query not implemented", true);
    },
    createRecord: function(store, type, record) {
      var data = this.mockJSON(type, record);
      Bridge.Comm.call_qt(Bridge.Ops.CREATE, this, store, type, {
        type: this.globalObjectType(type),
        record: data
      }, record);
    },
    updateRecord: function(store, type, record) {
      var data = this.mockJSON(type, record);
      Bridge.Comm.call_qt(Bridge.Ops.UPDATE, this, store, type, {
        type: this.globalObjectType(type),
        record: data
      }, record);
    },
    deleteRecord: function(store, type, record) {
      var data = this.mockJSON(type, record);
      Bridge.Comm.call_qt(Bridge.Ops.DELETE, this, store, type, {
        type: this.globalObjectType(type),
        record: data
      }, record);
    },
    /*
     @listener
     */
    invoked: function(op, adapter, store, type, request, data, localRecord) {
      switch (op) {
        case Bridge.Ops.FIND:
          adapter.didFindRecord(store, type, data, request.id);
          break;
        case Bridge.Ops.FINDALL:
          adapter.didFindAll(store, type, data);
          break;
        case Bridge.Ops.CREATE:
          adapter.didCreateRecord(store, type, localRecord, data);
          break;
        case Bridge.Ops.UPDATE:
          adapter.didUpdateRecord(store, type, localRecord, data);
          break;
        case Bridge.Ops.DELETE:
          adapter.didDeleteRecord(store, type, localRecord);
          break;
      }
    }

  });

  Bridge.Comm.init();

})();

