#ifndef MISSIONCREATOR_H
#define MISSIONCREATOR_H

#include "structs/missiondata.h"

class MissionCreator {
public:
    static const double MASS;
    static const double X0;
    static const double WAIT1;

    static simulator::data::InputMission empty();
    static simulator::data::InputMission fixedPoint();
    static simulator::data::InputMission wait1Trajectory();
};

#endif // MISSIONCREATOR_H
