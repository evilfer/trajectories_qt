
App.SimulationIndexController = Ember.ObjectController.extend({
  editingAttr: false,
  initialValue: false,
  editingTitle: function() {
    return this.editingAttr === 'title';
  }.property('editingAttr'),
  editTitle: function() {
    this.set('initialValue', this.get('title'));
    this.set('editingAttr', 'title');
  },
  acceptChanges: function() {
    this.set('editingAttr', false);
    this.get('model').save();
  }
});


