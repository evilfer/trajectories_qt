
App.AddMenuView = Ember.View.extend({
  templateName: 'addMenu',
  open: false,
  actions: {
    toggle: function() {
      this.set('open', !this.get('open'));
    }
  },
  close: function() {
    if (this.get('open')) {
      this.set('open', false);
    }

  },
  eventManager: Ember.Object.create({
    mouseLeave: function(event, view) {
      view.close();
    }
  })

});
