#ifndef MISSIONDATA_H
#define MISSIONDATA_H

#include "ephemerides/bodyconstants.h"

namespace simulator {

namespace data {

enum MissionObjectType {
    SHIP,
    ORBIT,
    STATE,
    WAIT
};


struct MissionObject {
    MissionObjectType type;

    MissionObject(MissionObjectType type) : type(type) {}
};


class InputMission : public std::vector<MissionObject*> {

public:
    virtual ~InputMission() {
        for (InputMission::iterator it = begin(); it != end(); it++) {
            MissionObject *obj = *it;
            delete obj;
        }
    }
};



struct MissionShip : MissionObject {

    double shipmass;
    double thrust;
    double isp;
    double fuelmass;

    MissionShip(double shipmass, double thrust, double isp, double fuelmass) :
        MissionObject(SHIP), shipmass(shipmass), thrust(thrust), isp(isp), fuelmass(fuelmass) {}

};


struct MissionOrbit : MissionObject {

    double et;
    ephemerides::BodyId body;
    double radius;
    double inc;
    double lon;
    double lat;

    MissionOrbit(double et, ephemerides::BodyId body, double radius, double inc, double lon, double lat) :
        MissionObject(ORBIT), et(et), body(body), radius(radius), inc(inc), lon(lon), lat(lat) {}

};

struct MissionState : MissionObject {
    double et;
    double pos[3];
    double vel[3];

    MissionState(double et, double x, double y, double z, double vx, double vy, double vz) :
        MissionObject(STATE), et(et), pos{x, y, z}, vel{vx, vy, vz} {}
};

struct MissionWait : MissionObject {
    double t;

    MissionWait(double t) :
        MissionObject(WAIT), t(t) {}
};

}
}


#endif // MISSIONDATA_H
