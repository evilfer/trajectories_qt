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


#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include "ship.h"
#include "solarsystem.h"

namespace world {


  class World {
    SolarSystem *solarsystem_;
    Ship *ship_;

    double et_;

  public:
    World(SolarSystem *solarsystem);
    virtual ~World();

    inline SolarSystem *solarSystem() {return this->solarsystem_;}
    inline Ship *ship() {return this->ship_;}
    inline const Ship *ship() const {return this->ship_;}

    double time() const {return this->et_;}

    void init(const simulator::data::MissionOrbit * orbit);
    void init(const simulator::data::MissionState * state);
    void step(double maxtime);
  };

}


#endif
