
App.EmbeddedTextFieldView = Ember.TextField.extend({
  classNames: ['edit'],
  size: 30,
  insertNewline: function() {
    this.get('parentView').acceptChanges();
  },
  focusOut: function() {
  //  this.get('parentView').acceptChanges();
  },
  didInsertElement: function() {
    this.$().focus();
  }
});


App.EmbeddedTextAreaView = Ember.TextArea.extend({
  classNames: ['edit'],
  rows: 15,
  cols: 30,
  focusOut: function() {
    this.get('parentView').acceptChanges();
  },
  didInsertElement: function() {
    this.$().focus();
  }
});
