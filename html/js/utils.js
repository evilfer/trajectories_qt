
App.Utils = {
  hasAttr: function(controller, attr) {
    var value = controller.get('model').get(attr);
    return value !== null && typeof value !== 'undefined';
  },
  optionalAttrAvailable: function(controller) {
    var optionalAttrs = controller.get('optionalAttrs');
    for (var i = 0; i < optionalAttrs.length; i++) {
      if (!this.hasAttr(controller, optionalAttrs[i])) {
        return true;
      }
    }
    
    return false;
  }
};


