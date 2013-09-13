
App.AddMenuView = Ember.View.extend({
  templateName: 'addMenu',
  open: false,
  actions: {
    toggle: function() {
      this.set('open', !this.get('open'));
    }
  }

});
