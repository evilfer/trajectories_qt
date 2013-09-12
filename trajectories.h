#ifndef TRAJECTORIES_H
#define TRAJECTORIES_H

#include "model/store.h"
#include "bridge/embercppjslistener.h"
#include "simulator/world/solarsystem.h"
#include "simulator/world/orbit.h"

class Trajectories : public bridge::EmberCppJsListener {

    model::Store * store_;

    world::SolarSystem *solarSystem_;


public:
    Trajectories();
    ~Trajectories();

    void init();

    virtual bool objectCreated(model::TObjectPtr obj);
    virtual void prepareCreateResponse(const std::string & type, QVariantMap & obj);
    virtual bool objectUpdated(model::TObjectPtr obj);
    virtual void prepareUpdateResponse(const std::string & type, QVariantMap & obj);

protected:
    bool objectChange(model::TObjectPtr obj, bool created);
    void prepareResponse(const std::string & type, QVariantMap & obj, bool created);

    void setSolarSystemBodies(QVariantMap & obj);

private:

    void addVector(const double* v, QVariantList & container) const;
    void addVector(const double* v, QVariantMap & container, const char *container_param) const;
    void addOrbit(const world::Orbit & orbit, QVariantMap & container, const char *container_param) const;
    bool fitInEphemeridesInterval(double & et, bool invalid = false) const;
};

#endif // TRAJECTORIES_H
