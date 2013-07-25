
App.InlineTextFieldView = Ember.View.extend({
  templateName: 'viewInlineTextField',
  isEditing: false,
  edit: function() {
    this.set('isEditing', true);
  },
  acceptChanges: function() {
    this.set('isEditing', false);
    this.get('controller').acceptChanges();
  }
});

App.InlineTextAreaView = Ember.View.extend({
  templateName: 'viewInlineTextArea',
  isEditing: false,
  edit: function() {
    this.set('isEditing', true);
  },
  acceptChanges: function() {
    this.set('isEditing', false);
    this.get('controller').acceptChanges();
  },
  formattedValue: function() {
    return this.get('value').replace(/\n\r?/g, '<br />');
  }.property('value').cacheable()
});
