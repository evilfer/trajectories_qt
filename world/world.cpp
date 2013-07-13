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


#include "world.h"
#include "../tmath/vectormath.h"

namespace world {

    World::World(SolarSystem *solarsystem) : et_(0) {
        this->solarsystem_ = solarsystem;
        this->ship_ = new Ship(this->solarsystem_);
    }

    World::~World() {
        delete this->ship_;
        delete this->solarsystem_;
    }

    void World::init(double et, ephemerides::BodyId id, double radius, double inc, double lon, double lat) {
        this->et_ = et;
        this->solarsystem_->wakeUpAllSystems();
        this->solarsystem_->update(et);
        this->ship_->setInOrbit(this->solarsystem_->body(id), radius, inc, lon, lat);
        this->solarsystem_->setAwakeSystem(this->ship_->closestSystem());
    }


    void World::setState(double et, const double *shippos, const double *shipvel) {
        this->et_ = et;
        this->solarsystem_->wakeUpAllSystems();
        this->solarsystem_->update(et);
        this->ship_->setState(shippos, shipvel);
        this->solarsystem_->setAwakeSystem(this->ship_->closestSystem());
    }

    void World::step(double maxtime) {
        double dt = this->ship_->calculateStepDuration();
        if (this->et_ + dt > maxtime) {
            dt = maxtime - this->et_;
        }

        this->et_ += dt;

        this->solarsystem_->update(this->et_);
        this->ship_->step(this->et_, dt);
        this->solarsystem_->setAwakeSystem(this->ship_->closestSystem());
    }


}
