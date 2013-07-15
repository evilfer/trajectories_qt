
App.ApplicationController = Ember.ObjectController.extend({
  testBridge: function() {
    BridgeManager.call_qt();
  }
});
