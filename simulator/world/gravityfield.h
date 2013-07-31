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

#ifndef WORLD_GRAVITYFIELD_H
#define WORLD_GRAVITYFIELD_H

#include "solarsystem.h"

namespace world {

class GravityField {
    SolarSystem * solarsystem_r;

    PlanetSystem * closest_r;
    Body * closestbody_r;
    double distance_;

    PlanetSystem * strongest_r;
    Body * strongestbody_r;
    double force_;

    void getAcc(const double *pos, double *acc, Body *body, PlanetSystem *owner);

public:
    GravityField(SolarSystem * solarsystem);
    virtual ~GravityField();
    
    void updateAccDistance(const double *pos, double *acc);

    inline double minDistance() const {return this->distance_;}
    inline PlanetSystem * closestSystem() {return this->closest_r;}
};

}

#endif
