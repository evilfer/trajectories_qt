
App.ObjectVariableParamsController = Ember.ObjectController.extend({
  _hasAttr: function(attr) {
    var value = this.get('model').get(attr);
    return value !== null && typeof value !== 'undefined';
  },
  _availableOptionalAttrs: function() {
    var list = [];
    var optionalAttrs = this.get('optionalAttrs');
    for (var i = 0; i < optionalAttrs.length; i++) {
      if (!this._hasAttr(optionalAttrs[i].key)) {
        list.push(optionalAttrs[i]);
      }
    }
    return list;
  },
  _hasAvailableOptionalAttrs: function() {
    var optionalAttrs = this.get('optionalAttrs');
    for (var i = 0; i < optionalAttrs.length; i++) {
      if (!this._hasAttr(optionalAttrs[i].key)) {
        return true;
      }
    }
    return false;
  }
});

