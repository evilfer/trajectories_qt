#include "trajectories.h"

#include "simulator/ephemerides/spiceposition.h"
#include "simulator/world/worldloader.h"
#include "simulator/tmath/consts.h"

#include <iostream>

Trajectories::Trajectories() : EmberCppJsListener() {
    this->init();
    this->solarSystem_ = world::WorldLoader::loadSolarSystem();
    this->solarSystem_->wakeUpAllSystems();
}

Trajectories::~Trajectories() {
    delete this->solarSystem_;
}

bool Trajectories::objectCreated(model::TObjectPtr obj) {
    return this->objectChange(obj, true);
}

bool Trajectories::objectUpdated(model::TObjectPtr obj) {
    return this->objectChange(obj, false);
}

void Trajectories::prepareCreateResponse(const std::string & type, QVariantMap & record) {
    this->prepareResponse(type, record, true);
}

void Trajectories::prepareUpdateResponse(const std::string & type, QVariantMap & record) {
    this->prepareResponse(type, record, false);
}

bool Trajectories::objectChange(model::TObjectPtr obj, bool) {
    if (obj->type() == "solar_system_state") {
        double et = obj->getDouble("date");
        if (this->fitInEphemeridesInterval(et, obj->emptyDouble("date"))) {
            obj->setDouble("date", et);
            return true;
        }
    }

    return false;
}

void Trajectories::prepareResponse(const std::string &type, QVariantMap &obj, bool) {
    if (type == "solar_system_state") {
        this->setSolarSystemBodies(obj);
    }
}

void Trajectories::setSolarSystemBodies(QVariantMap & obj) {
    QVariantMap qbodies = QVariantMap();
    this->solarSystem_->update(obj["date"].toDouble());

    world::Orbit orbit;

    const world::BodyList & bodies = this->solarSystem_->bodies();
    for (world::BodyConstIterator i = bodies.begin(); i != bodies.end(); i++) {
        const world::Body * body = (*i);
        QVariantMap state = QVariantMap();
        this->addVector(body->pos(), state, "pos");
        this->addVector(body->vel(), state, "vel");

        ephemerides::BodyId parent = body->parent();
        if (parent) {
            orbit.set(this->solarSystem_->body(parent), body);
            this->addOrbit(orbit, state, "orbit");
        }

        qbodies[body->name().c_str()] = state;
    }

    obj["bodies"] = qbodies;
}

void Trajectories::addVector(const double* v, QVariantMap & container, const char *container_param) const {
    QVariantList qlist = QVariantList();
    qlist.append(v[0]);
    qlist.append(v[1]);
    qlist.append(v[2]);
    container[container_param] = qlist;
}
void Trajectories::addVector(const double* v, QVariantList & container) const {
    QVariantList qlist = QVariantList();
    qlist.append(v[0]);
    qlist.append(v[1]);
    qlist.append(v[2]);
    container.push_back(qlist);
}

void Trajectories::addOrbit(const world::Orbit & orbit, QVariantMap & container, const char *container_param) const {
    QVariantList qlist = QVariantList();
    double p[3];
    int n = 100;
    double da = 2 * M_PI / n;
    for (int i = 0; i < n; i++) {
        orbit.calculateGlobalPosition(da * i, p);
        this->addVector(p, qlist);
    }
    container[container_param] = qlist;
}


bool Trajectories::fitInEphemeridesInterval(double &et, bool invalid) const {
    const ephemerides::EphemeridesInterval & interval = ephemerides::SpicePosition::interval();

    if (invalid || et < interval.a) {
        et = interval.a;
        return true;
    } else if (et > interval.b) {
        et = interval.b;
        return true;
    } else {
        return false;
    }
}


