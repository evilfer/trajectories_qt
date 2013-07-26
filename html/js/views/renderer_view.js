
App.RendererView = Ember.View.extend({
  classNames: ['t-canvas'],
  willDestroyElement: function() {
  },
  didInsertElement: function() {
    var $container = $('.t-canvas');

    var viewAngle = 45,
            near = 0.1,
            far = 10000;

    var renderer = new THREE.WebGLRenderer({clearColor: 0x202020, clearAlpha: 1});
    var camera = new THREE.PerspectiveCamera(viewAngle, 1, near, far);
    var scene = new THREE.Scene();
    scene.add(camera);

    camera.position.z = 300;

    $container.append(renderer.domElement);
    var $canvas = $container.find('canvas');

    var radius = 50,
            segments = 32,
            rings = 32;

    var sphereMaterial = new THREE.MeshLambertMaterial({color: 0xCCFF00});
    var sphere = new THREE.Mesh(new THREE.SphereGeometry(radius, segments, rings), sphereMaterial);

    scene.add(sphere);

    var pointLight = new THREE.PointLight(0xFFFFFF);

    pointLight.position.x = 10;
    pointLight.position.y = 50;
    pointLight.position.z = 130;

    scene.add(pointLight);

    var resizeF = function() {
      var width = $container.width();
      var height = $container.height();

      renderer.setSize(width, height);
      camera.aspect = width / height;
      camera.updateProjectionMatrix();
    };
    
    $container.resize(resizeF);
    resizeF();

    (function animate() {
      requestAnimationFrame(animate);
      renderer.render(scene, camera);
    })();
  }
});
