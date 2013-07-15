
var CppJavascriptBridge = {
    call_js: function() {
        alert('js called!');
    },

    call_qt: function() {
        Qt.call_qt();
    }
};

$(function() {
    Qt.call_js.connect(call_js);

    $('#test_bridge').click(function() {
        CppJavascriptBridge.call_qt();
    });
});

