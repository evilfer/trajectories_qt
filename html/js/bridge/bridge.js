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
    promises: {},
    enabled: false,
    init: function() {
      if (typeof QtCppJsBridge !== 'undefined') {
        this.enabled = true;
        QtCppJsBridge.call_js_obj.connect(Bridge.Comm.call_js_obj);
        QtCppJsBridge.call_js_array.connect(Bridge.Comm.call_js_array);
      }
    },
    call_js_obj: function(opId, complete, answer) {
      Bridge.Comm.processJsCall(opId, complete, answer);
    },
    call_js_array: function(opId, complete, answer) {
      Bridge.Comm.processJsCall(opId, complete, answer);
    },
    processJsCall: function(opId, complete, answer) {
      console.log(answer);
      var promise = this.promises[opId];
      if (promise) {
        //promise.resolve(answer);
        if (complete) {
          delete this.promises[opId];
        }
        Ember.run(null, promise.resolve, answer);
      }
    },
    call_qt: function(op, data) {
      var id = this.opId;
      this.opId++;

      var adapter = this;
      return new Ember.RSVP.Promise(function(resolve, reject) {
        //Ember.run(null, resolve, {'simulations': []});
        adapter.promises[id] = {
          resolve: resolve,
          reject: reject
        };
        QtCppJsBridge.call_qt(op, id, data);
      });
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
    serializeRecord: function(record) {
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
    generateIdForRecord: null,
            
    find: function(store, type, id) {
      return Bridge.Comm.call_qt(Bridge.Ops.FIND, {
        type: this.globalObjectType(type),
        id: id
      });
    },
    findMany: function(store, type, ids) {
      Ember.assert("find many not implemented", true);
    },
    findAll: function(store, type) {
      return Bridge.Comm.call_qt(Bridge.Ops.FINDALL, {
        type: this.globalObjectType(type)
      });
    },
    findQuery: function(store, type, query, array) {
      Ember.assert("find query not implemented", true);
    },
    createRecord: function(store, type, record) {
      var data = this.serializeRecord(record);
      console.log('create: ' + type);
      console.log(data);
      return Bridge.Comm.call_qt(Bridge.Ops.CREATE, {
        type: this.globalObjectType(type),
        record: data
      });
    },
    updateRecord: function(store, type, record) {
      var data = this.serializeRecord(record);
      console.log('update: ' + type);
      console.log(data);
      return Bridge.Comm.call_qt(Bridge.Ops.UPDATE, {
        type: this.globalObjectType(type),
        record: data
      });
    },
    deleteRecord: function(store, type, record) {
      var data = this.serializeRecord(record);
      return Bridge.Comm.call_qt(Bridge.Ops.DELETE, {
        type: this.globalObjectType(type),
        record: data
      });
    }
  });

  Bridge.Comm.init();

})();

