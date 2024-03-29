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

#ifndef WORLD_SHIP_H
#define WORLD_SHIP_H

#include "object.h"
#include "gravityfield.h"
#include "burn.h"
#include "structs/missiondata.h"

namespace world {

    typedef double ShipSystemsState;

    class Ship : public Object {
        double acc_[3];
        SolarSystem * solarsystem_;
        GravityField * gravity_;

        double shipmass_;
        double thrust_;
        double isp_;
        double fuelmass_;
        double ve_;

        double current_fuelmass_;
        Burn *burn_;

        void computeManeuverStep(double et);

    public:
        Ship(SolarSystem * solarsystem);
        ~Ship();

        void setShipSystemsState(const ShipSystemsState & state);
        void getShipSystemsState(ShipSystemsState & state) const;

        const double * acc() const {return this->acc_;}
        double * acc() {return this->acc_;}

        void setInOrbit(const simulator::data::MissionOrbit* orbit);
        void setState(const simulator::data::MissionState* state);
        void setState(const double *pos, const double *vel);
        void step(double t, double dt);

        void set(const simulator::data::MissionShip* data);


        inline double minDistance() const {return this->gravity_->minDistance();}
        inline const PlanetSystem * closestSystem() const {return this->gravity_->closestSystem();}
        inline PlanetSystem * closestSystem() {return this->gravity_->closestSystem();}

        double calculateStepDuration() const;

        bool hasFuel() const {return this->current_fuelmass_ > .0;}
        void calculateBurn(const double *dv, double maneuverTime);
        void startBurn();
        void endBurn();

        double shipmass() const {return shipmass_;}
    };
}

#endif // SHIP_H
