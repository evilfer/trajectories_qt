
App.SimulationIndexController = Ember.ObjectController.extend({
  editingAttr: false,
  editingTitle: function() {
    return this.editingAttr === 'title';
  }.property('editingAttr'),
  editingDescription: function() {
    return this.editingAttr === 'description';
  }.property('editingAttr'),
  editTitle: function() {
    this.set('editingAttr', 'title');
  },
  editDescription: function() {
    this.set('editingAttr', 'description');
  },
  acceptChanges: function(field) {
    if (field === this.get('editingAttr')) {
      this.set('editingAttr', false);
      this.get('model').save();
    }
  },
  formattedDescription: function() {
    return this.get('description').replace(/\n\r?/g, '<br />');
  }.property('description').cacheable()
});


