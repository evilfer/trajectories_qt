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

#include "ship.h"
#include "tmath/vectormath.h"

namespace world {
    Ship::Ship(SolarSystem * solarsystem) : Object()
    {
        tvector::reset(this->acc_);
        this->gravity_ = new GravityField(solarsystem);
    }

    Ship::~Ship() {
        delete this->gravity_;
    }

    void Ship::setInOrbit(const Body * body, double radius, double inc, double lon, double lat) {
        // set in orbit;
        this->gravity_->updateAccDistance(this->pos(), this->acc_);
    }

    void Ship::setState(const double *pos, const double *vel) {
        tvector::set(pos, this->pos_);
        tvector::set(vel, this->vel_);

        this->gravity_->updateAccDistance(this->pos(), this->acc_);
    }


    double Ship::calculateStepDuration() const {
        double dt = this->gravity_->minDistance() / (tvector::mod(this->vel_) * 5000);
        if (dt < .1) {
            dt = .1;
        }

        // do other checks, for the case of burns

        return dt;
    }

    void Ship::step(double t, double dt) {
        // do stop staff, including:

        this->gravity_->updateAccDistance(this->pos(), this->acc_);
    }

}
