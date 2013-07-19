
App.EditSimulationMetadataTitleView = Ember.TextField.extend({
  classNames: ['edit'],
  size: 30,
  insertNewline: function() {
    this.get('controller').acceptChanges('title');
  },
  focusOut: function() {
    this.get('controller').acceptChanges('title');
  },
  didInsertElement: function() {
    this.$().focus();
  }
});


App.EditSimulationMetadataDescriptionView = Ember.TextArea.extend({
  classNames: ['edit'],
  rows: 15,
  cols: 30,
  focusOut: function() {
    this.get('controller').acceptChanges('description');
  },
  didInsertElement: function() {
    this.$().focus();
  }
});
