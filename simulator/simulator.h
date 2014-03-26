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

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "world/world.h"
#include "trajectory/trajectory.h"

#include "structs/missiondata.h"

namespace simulator {


class Simulator {

    world::World * world_;

    trajectory::Trajectory trajectory_;

    bool typeOk(int &state, const data::MissionObjectType & type);


    void initShip(const data::MissionShip* ship);
    void createStateSection(const data::MissionState* state);
    void createOrbitSection(const data::MissionOrbit* orbit);

    void createPointSection();

    void simulate(int state, const data::InputMission& mission, const data::InputMission::const_iterator missionItem);

public:
    Simulator(world::SolarSystem * solarsystem);
    void simulate(const data::InputMission& mission);

    const trajectory::Trajectory& trajectory() const {return trajectory_;}

    const world::World* world() const {return world_;}
};

}

#endif // SIMULATOR_H
