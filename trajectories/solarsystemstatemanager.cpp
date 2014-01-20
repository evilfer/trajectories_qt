#include "solarsystemstatemanager.h"

#include "../simulator/world/worldloader.h"
#include "../simulator/ephemerides/spiceposition.h"
#include "../simulator/tmath/consts.h"

#include <iostream>

SolarSystemStateManager::SolarSystemStateManager() : solarsystem_m(NULL), orbit_m(), ids_m(), lastCenter(-1), lastEt() {
    this->solarsystem_m = world::WorldLoader::loadSolarSystem();
    this->solarsystem_m->wakeUpAllSystems();

    for (world::BodyConstIterator it = solarsystem_m->bodies().begin(); it != solarsystem_m->bodies().end(); it++) {
        const world::Body * body = (*it);
        ids_m[body->id()] = QString::number(body->id());
    }
}

SolarSystemStateManager::~SolarSystemStateManager() {

}



void SolarSystemStateManager::timeInterval(QVariantMap &, QVariantMap &result) {
    const ephemerides::EphemeridesInterval & interval = ephemerides::SpicePosition::interval();
    result["a"] = interval.a;
    result["b"] = interval.b;
}

void SolarSystemStateManager::solarSystemBodies(QVariantMap &, QVariantMap &result) {

    QVariantMap bodies;
    QVariantMap treeRoot;

    std::map<int, std::vector<int>> children;

    for (world::BodyConstIterator it = solarsystem_m->bodies().begin(); it != solarsystem_m->bodies().end(); it++) {
        const world::Body * body = (*it);
        QVariantMap bodyConstants;

        bodyConstants["id"] = body->id();
        if (body->parent()) {
            bodyConstants["parent"] = body->parent();
            children[body->parent()].push_back(body->id());
        } else {
            bodyConstants["parent"] = false;
        }
        bodyConstants["name"] = QString::fromStdString(body->name());
        bodyConstants["radius"] = body->radius();
        bodyConstants["mass"] = body->mass();

        bodies[ids_m[body->id()]] = bodyConstants;
    }

    result["bodies"] = bodies;

    if (solarsystem_m->sun()) {
        this->buildBodyTree(children, treeRoot, solarsystem_m->sun()->id());
    }

    result["tree"] = treeRoot;

}

void SolarSystemStateManager::buildBodyTree(std::map<int, std::vector<int>> & tree, QVariantMap &container, int body) {

    std::vector<int> & childsChildren = tree[body];
    if (childsChildren.size() == 0) {
        container[ids_m[body]] = false;
    } else {
        QVariantMap childrenObj;
        for (std::vector<int>::const_iterator it = childsChildren.begin(); it != childsChildren.end(); it++) {
            this->buildBodyTree(tree, childrenObj, *it);
        }
        container[ids_m[body]] = childrenObj;
    }
}

void SolarSystemStateManager::solarSystemState(QVariantMap &data, QVariantMap &result) {

    const ephemerides::EphemeridesInterval & interval = ephemerides::SpicePosition::interval();

    bool update = false;

    bool ok;

    int center = data["center"].toInt(&ok);
    if (ok && this->lastCenter != center) {
        this->lastCenter = center;
        update = true;
    }

    double et = data["et"].toDouble(&ok);
    if (ok) {
        interval.putInRange(et);
    } else {
        et = interval.a;
    }

    if (et != this->lastEt) {
        this->lastEt = et;
        update = true;
    }

    if (update) {
        this->solarsystem_m->update(this->lastEt);
    }

    const world::Body *centerBody = solarsystem_m->bodies().get(this->lastCenter);

    addBodyState(this->solarsystem_m->sun(), centerBody, result);

    for (world::PlanetSystemList::iterator it = solarsystem_m->planets().begin(); it != solarsystem_m->planets().end(); it++) {
        world::PlanetSystem * ps = (*it);
        //if (ps->simplemode()) {
        //    addBodyState(ps->baricenter(), ps->main()->id(), centerBody, result);
        //} else {
        for(world::BodyVector::iterator bit = ps->bodies().begin(); bit != ps->bodies().end(); bit++) {
            world::Body * b = (*bit);
            addBodyState(b, centerBody, result);
        }
        // }
    }

}

void SolarSystemStateManager::addBodyState(const world::Body *body, int code, const world::Body *center, QVariantMap &states) {

    static int orbitN = 100;
    static double i2p = M_PI / orbitN;

    static double orbitPos[3];

    QVariantMap state;

    SolarSystemStateManager::vector2map(body->pos(), center->pos(), state, "pos");
    SolarSystemStateManager::vector2map(body->vel(), center->pos(), state, "vel");

    std::cout << body->id() << " " << body->parent() << std::endl;

    if (body->parent()) {
        QVariantList orbit;

        if (body->hasIrregularOrbit()) {
            for (int i = 0; i < body->irregularOrbit()->size(); i++) {
                SolarSystemStateManager::vector2list(body->irregularOrbit()->get(i), center->pos(), orbit);
            }
        } else {
            const world::Body * parent = solarsystem_m->bodies().get(body->parent());
            orbit_m.set(parent, body);

            double a0 = orbit_m.trueAnomaly();

            for (int i = 0; i < orbitN; i++) {
                double a = a0 + M_PI * (1 - cos(i2p * i));
                orbit_m.calculateGlobalPosition(a, orbitPos);
                SolarSystemStateManager::vector2list(orbitPos, center->pos(), orbit);
            }

            orbit.append(orbit.at(0));
        }

        state["orbit"] = orbit;
    } else {
        state["orbit"] = false;
    }


    states[ids_m[code]] = state;

}

void SolarSystemStateManager::vector2map(const double* vector, const double* ref, QVariantMap &result, const QString &key) {
    QVariantMap v;
    v["x"] = vector[0] - ref[0];
    v["y"] = vector[1] - ref[1];
    v["z"] = vector[2] - ref[2];
    result[key] = v;
}
void SolarSystemStateManager::vector2list(const double* vector, const double* ref, QVariantList &list) {
    QVariantMap v;
    v["x"] = vector[0] - ref[0];
    v["y"] = vector[1] - ref[1];
    v["z"] = vector[2] - ref[2];
    list.append(v);
}
/*void SolarSystemStateManager::vector2list(const double* vector, QVariantList &list) {
    list.append(vector[0]);
    list.append(vector[1]);
    list.append(vector[2]);
}*/

