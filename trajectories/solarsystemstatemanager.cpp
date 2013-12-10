#include "solarsystemstatemanager.h"

#include "simulator/world/worldloader.h"
#include "simulator/ephemerides/spiceposition.h"

SolarSystemStateManager::SolarSystemStateManager() : solarsystem_m(NULL), ids_m() {
    this->solarsystem_m = world::WorldLoader::loadSolarSystem();
    this->solarsystem_m->wakeUpAllSystems();

    for (world::BodyConstIterator it = solarsystem_m->bodies().begin(); it != solarsystem_m->bodies().end(); it++) {
        const world::Body * body = (*it);
        ids_m[body->id()] = QString::number(body->id());
    }
}

SolarSystemStateManager::~SolarSystemStateManager() {
    delete this->solarsystem_m;
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

    bool ok;
    double et = data["et"].toDouble(&ok);

    if (ok) {
        interval.putInRange(et);
    } else {
        et = interval.a;
    }

    solarsystem_m->update(et);

    for (world::BodyConstIterator it = solarsystem_m->bodies().begin(); it != solarsystem_m->bodies().end(); it++) {
        const world::Body * body = (*it);
        QVariantMap state;

        SolarSystemStateManager::vector2map(body->pos(), state, "pos");
        SolarSystemStateManager::vector2map(body->vel(), state, "vel");

        result[ids_m[body->id()]] = state;
    }
}

void SolarSystemStateManager::vector2map(const double* vector, QVariantMap &result, const QString &key) {
    QVariantList list;
    for (int i = 0; i < 3; i++) {
        list.append(vector[i]);
    }
    result[key] = list;
}

