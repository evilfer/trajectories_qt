var tRenderer = function (element, model) {

    this.model = model;
    this.objects = {};

    this.settings = {
        segments: 32,
        rings: 32,
        sphereMaterial: new THREE.MeshLambertMaterial({color: 0x00FF00}),
        lineMaterial: new THREE.LineBasicMaterial({color: 0xe0e0e0, lineWidth: 2})
    };

    var self = this;

    var $container = angular.element(element);

    var viewAngle = 45,
        near = 1,
        far = 40000000;

    this.renderer = new THREE.WebGLRenderer();
    this.renderer.setClearColor(0x202020, 1);
    this.camera = new THREE.PerspectiveCamera(viewAngle, 1, near, far);
    this.scene = new THREE.Scene();
    this.scene.add(this.camera);

    var renderF = function () {
        self.renderer.render(self.scene, self.camera);
    };


    this.controls = new THREE.TrackballControls(this.camera, this.renderer.domElement);

    this.controls.addEventListener('change', renderF);

    $container.append(this.renderer.domElement);

    var pointLight = new THREE.PointLight(0xFFF);

    pointLight.position.x = 0;
    pointLight.position.y = 0;
    pointLight.position.z = 0;

    this.scene.add(pointLight);

    var ambientLight = new THREE.AmbientLight(0xAAA);
    this.scene.add(ambientLight);

    var resizeF = function () {
        var width = $container.width();
        var height = $container.height();

        self.renderer.setSize(width, height);
        self.camera.aspect = width / height;
        self.camera.updateProjectionMatrix();
        self.controls.handleResize();
        renderF();
    };

    $container.resize(resizeF);
    resizeF();

    (function animate() {
        requestAnimationFrame(animate);
        self.controls.update();
    })();
};

tRenderer.prototype.clear = function() {
    for (var i in this.objects) {
        this.scene.remove(this.objects[i]);
    }
};

tRenderer.prototype.updateScene = function () {
    this.clear();

    /*var segments = 32;
    var rings = 32;

    var sphere = new THREE.Mesh(new THREE.SphereGeometry(radius, segments, rings), sphereMaterial);
    this.scene.add(sphere);

    var sphereMaterial2 = new THREE.MeshLambertMaterial({color: 0x0000FF});
    var sphere2 = new THREE.Mesh(new THREE.SphereGeometry(.5 * radius, segments, rings), sphereMaterial2);
    this.scene.add(sphere2);
    sphere2.position.x += 100;


    var lineGeometry = new THREE.Geometry();
    var lineN = 100;
    var lineA = 2 * Math.PI / lineN;
    for (var i = 0; i <= lineN; i++) {
        lineGeometry.vertices.push(new THREE.Vector3(100 * Math.cos(i * lineA), 100 * Math.sin(i * lineA), 0));
    }
    var line = new THREE.Line(lineGeometry, lineMaterial);
    this.scene.add(line);
*/
    for (var id in this.model.state) {
        this.addBodyLines(id);
    }

    for (var id in this.model.state) {
        this.addBody(id);
    }

    this.updateCamera();
    this.renderer.render(this.scene, this.camera);
};

tRenderer.prototype.updateCamera = function() {
    var id = this.model.center;

    var bodyPos = this.model.state[id].pos;


    this.camera.position.set(bodyPos.x, bodyPos.y, bodyPos.z + 8 * this.model.bodies[id].radius);
    this.camera.up = new THREE.Vector3(0,1,0);
    this.camera.lookAt(new THREE.Vector3(bodyPos.x, bodyPos.y, bodyPos.z));

    this.controls.target.set(bodyPos.x, bodyPos.y, bodyPos.z);
    this.controls.update();
};

tRenderer.prototype.addBodyLines = function(id) {

    var state = this.model.state[id];

    if (state.orbit) {
        var body = this.model.bodies[id];
        var orbitGeometry = new THREE.Geometry();
        for (var i = 0; i < state.orbit.length; i++) {
            var p = state.orbit[i];
            orbitGeometry.vertices.push(new THREE.Vector3(p.x, p.y, p.z));
        }
        var orbit = new THREE.Line(orbitGeometry, this.settings.lineMaterial);
        this.scene.add(orbit);
        this.objects[id+":o"] = orbit;

        var posGeometry = new THREE.Geometry();
        var parentPos = this.model.state[body.parent].pos;
        posGeometry.vertices.push(new THREE.Vector3(parentPos.x, parentPos.y, parentPos.z));
        posGeometry.vertices.push(new THREE.Vector3(state.pos.x, state.pos.y, state.pos.z));

        var posList = new THREE.Line(posGeometry, this.settings.lineMaterial);
        this.scene.add(posList);
        this.objects[id+":p"] = posList;
    }
};

tRenderer.prototype.addBody = function(id) {
    var body = this.model.bodies[id];
    var state = this.model.state[id];

    var sphere = new THREE.Mesh(new THREE.SphereGeometry(body.radius, this.settings.segments, this.settings.rings), this.settings.sphereMaterial);

    sphere.position.x = state.pos.x;
    sphere.position.y = state.pos.y;
    sphere.position.z = state.pos.z;

    this.scene.add(sphere);
    this.objects[id] = sphere;

};