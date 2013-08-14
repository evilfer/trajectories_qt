
App.RendererView = Ember.View.extend({
  classNames: ['t-canvas'],
  willDestroyElement: function() {
  },
  didInsertElement: function() {
    var $container = $('.t-canvas');

    var viewAngle = 45,
            near = 0.1,
            far = 10000;

    var renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(0x202020, 1);
    var camera = new THREE.PerspectiveCamera(viewAngle, 1, near, far);
    var scene = new THREE.Scene();
    scene.add(camera);

    camera.position.z = 300;

    var renderF = function() {
      renderer.render(scene, camera);
    };


    var controls = new THREE.TrackballControls(camera, renderer.domElement);

    controls.addEventListener('change', renderF);

    $container.append(renderer.domElement);

    var radius = 50,
            segments = 32,
            rings = 32;

    var sphereMaterial = new THREE.MeshLambertMaterial({color: 0xCCFF00});
    var sphere = new THREE.Mesh(new THREE.SphereGeometry(radius, segments, rings), sphereMaterial);
    scene.add(sphere);

    var sphereMaterial2 = new THREE.MeshLambertMaterial({color: 0xCC00FF});
    var sphere2 = new THREE.Mesh(new THREE.SphereGeometry(.5 * radius, segments, rings), sphereMaterial2);
    scene.add(sphere2);
    sphere2.position.x += 100;

    var lineMaterial = new THREE.LineBasicMaterial({color: 0xe0e0e0, lineWidth: 2});
    var lineGeometry = new THREE.Geometry();
    var lineN = 100;
    var lineA = 2 * Math.PI / lineN;
    for (var i = 0; i <= lineN; i++) {
      lineGeometry.vertices.push(new THREE.Vector3(100 * Math.cos(i * lineA), 100 * Math.sin(i * lineA), 0));
    }
    var line = new THREE.Line(lineGeometry, lineMaterial);
    scene.add(line);

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
      controls.handleResize();
      renderF();
    };

    $container.resize(resizeF);
    resizeF();

    (function animate() {
      requestAnimationFrame(animate);
      controls.update();
    })();
  }
});

