
var nspWatchers = function() {
  this.watches = [];
};

nspWatchers.prototype.watch = function(scope, property, callback) {
  this.watches.push(scope.$watch(property, callback));
};

nspWatchers.prototype.unwatch = function() {
  for (var i = 0; i < this.watches.length; i++) {
    this.watches[i]();
  }
};
