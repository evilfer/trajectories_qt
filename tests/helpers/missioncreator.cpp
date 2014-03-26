#include "missioncreator.h"


const double MissionCreator::MASS = 1000;
const double MissionCreator::X0 = 1000;
const double MissionCreator::WAIT1 = 10;


simulator::data::InputMission MissionCreator::empty() {
    simulator::data::InputMission mission;
    mission.push_back(new simulator::data::MissionShip(MASS, 1000, 100, 1000));
    return mission;
}

simulator::data::InputMission MissionCreator::fixedPoint() {
    simulator::data::InputMission mission = empty();
    mission.push_back(new simulator::data::MissionState(0, X0, 0, 0, 0, 0, 0));
    return mission;
}

simulator::data::InputMission MissionCreator::wait1Trajectory() {
    simulator::data::InputMission mission = fixedPoint();
    mission.push_back(new simulator::data::MissionWait(WAIT1));
    return mission;
}
