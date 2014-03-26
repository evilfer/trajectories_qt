/*

Copyright (C) 2010-2013 Eloy David Villasclaras Fernandez.
evilfer@gmail.com

This file is part of Trajectories.

Trajectories is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Trajectories is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Trajectories.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "simulator.h"

namespace simulator {


Simulator::Simulator(world::SolarSystem *solarsystem) : world_(new world::World(solarsystem)), trajectory_(world_) {
}


void Simulator::simulate(int state, const data::InputMission& mission, const data::InputMission::const_iterator missionIt) {
    if (missionIt != mission.end()) {
        const data::MissionObject * obj = *missionIt;
        if (typeOk(state, obj->type)) {
            switch(obj->type) {
            case data::MissionObjectType::SHIP:
                initShip((const data::MissionShip*) obj);
                break;
            case data::MissionObjectType::ORBIT:
                createOrbitSection((const data::MissionOrbit*) obj);
                break;
            case data::MissionObjectType::STATE:
                createStateSection((const data::MissionState*) obj);
                break;
            }

            simulate(state, mission, missionIt + 1);
        }
    }

}


void Simulator::simulate(const data::InputMission& mission) {
    trajectory_.clear();
    simulate(0, mission, mission.begin());
}

bool Simulator::typeOk(int &state, const data::MissionObjectType & type) {
    switch(type) {
    case data::MissionObjectType::SHIP:
        if (state == 0) {
            state = 1;
            return true;
        }
        break;
    case data::MissionObjectType::STATE:
    case data::MissionObjectType::ORBIT:
        if (state == 1) {
            state = 2;
            return true;
        }
        break;
    default:
        if (state == 2) {
            return true;
        }
        break;
    }

    return false;
}

void Simulator::initShip(const data::MissionShip* data) {
    world_->ship()->set(data);
}

void Simulator::createStateSection(const data::MissionState* state) {
    world_->init(state);
    createPointSection();
}

void Simulator::createOrbitSection(const data::MissionOrbit* orbit) {
    world_->init(orbit);
    createPointSection();
}

void Simulator::createPointSection() {
    trajectory_.savePoint();
    trajectory_.initNewSection();
    trajectory_.completeSection();
}


}
