
var BridgeManager = {
  call_js: function() {
    alert('js called!');
  },
  call_qt: function() {
    console.log('call qt!');
    QtCppJsBridge.call_qt();
  }
};

$(function() {
  if (typeof QtCppJsBridge !== 'undefined') {
    QtCppJsBridge.call_js.connect(BridgeManager.call_js);
  }
});
