#ifndef SOLARSYSTEMSTATEMANAGER_H
#define SOLARSYSTEMSTATEMANAGER_H


#include <QVariantMap>
#include <map>
#include <vector>

#include "../simulator/world/solarsystem.h"
#include "../simulator/world/orbit.h"

class SolarSystemStateManager {
    world::SolarSystem * solarsystem_m;
    world::Orbit orbit_m;

    std::map<int, QString> ids_m;

    ephemerides::BodyId lastCenter;
    double lastEt;

public:
    SolarSystemStateManager();
    ~SolarSystemStateManager();

    void timeInterval(QVariantMap &data, QVariantMap &result);
    void solarSystemBodies(QVariantMap &data, QVariantMap &result);
    void solarSystemState(QVariantMap &data, QVariantMap &result);
    inline void addBodyState(const world::Body *body, QVariantMap &states) {addBodyState(body, body->id(), states);}
    void addBodyState(const world::Body *body, int code, QVariantMap &states);

    void buildBodyTree(std::map<int, std::vector<int>> & tree, QVariantMap &container, int body);

    static void vector2map(const double* vector, QVariantMap &result, const QString &key);
    static void vector2list(const double* vector, QVariantList &list);
};

#endif // SOLARSYSTEMSTATEMANAGER_H
