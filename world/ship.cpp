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
#include "tmath/consts.h"

namespace world {
    Ship::Ship(SolarSystem * solarsystem) : Object()
    {
        this->set(0, 0, 0, 0);
        tvector::reset(this->acc_);
        this->gravity_ = new GravityField(solarsystem);
        this->burn_ = new Burn();
    }

    Ship::~Ship() {
        delete this->gravity_;
    }

    void Ship::setShipSystemsState(const ShipSystemsState & state) {
        this->current_fuelmass_ = state;
    }

    void Ship::getShipSystemsState(ShipSystemsState & state) {
        state = this->current_fuelmass_;
    }

    void Ship::setInOrbit(const Body * body, double radius, double inc, double lon, double lat) {

        double a = radius * cos(lat);
        double pa = radius * cos(inc) * sin(lat);
        double x = a * cos(lon) - pa * sin(lon);
        double y = a * sin(lon) + pa * cos(lon);
        double z = radius * sin(inc) * sin(lat);

        double v = sqrt(body->gm() / radius);

        double va = -v * sin(lat);
        double vpa = v * cos(inc) * cos(lat);
        double vx = va * cos(lon) - vpa * sin(lon);
        double vy = va * sin(lon) + vpa * cos(lon);
        double vz = v * sin(inc) * cos(lat);

        tvector::set(x, y, z, this->pos_);
        tvector::add(this->pos_, body->pos());
        tvector::set(vx, vy, vz, this->vel_);
        tvector::add(this->vel_, body->vel());

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

        if (this->burn_->burning() && this->burn_->maxStep() < dt) {
            dt = this->burn_->maxStep();
        }

        return dt;
    }

    void Ship::step(double et, double dt) {
        if (this->burn_->burning()) {
            this->burn_->computeBurnStep(et);
        }

        double hdt = .5 * dt;
        tvector::addScaled(this->pos_, this->vel_, dt);
        tvector::addScaled(this->pos_, this->acc_, hdt*dt);

        tvector::addScaled(this->vel_, this->acc_, hdt);
        this->gravity_->updateAccDistance(this->pos_, this->acc_);
        tvector::addScaled(this->vel_, this->acc_, hdt);

        if (this->burn_->burning()) {
            this->burn_->computeBurnStep(et);
            tvector::add(this->vel_, this->burn_->stepAcc());
        }
    }

    void Ship::set(double shipmass, double thrust, double isp, double fuelmass) {
        this->shipmass_ = shipmass;
        this->thrust_ = thrust;
        this->isp_ = isp;
        this->fuelmass_ = fuelmass;
        this->ve_ = MT_G0 * this->isp_;

        this->current_fuelmass_ = fuelmass_;
    }

    void Ship::calculateBurn(const double *dv, double maneuverTime) {
        this->burn_->calculateBurn(dv, maneuverTime, this->shipmass_, this->current_fuelmass_, this->thrust_, this->ve_);
    }

    void Ship::startBurn() {
        this->burn_->startBurn();
    }

    void Ship::endBurn() {
        this->burn_->stopBurn();
        this->current_fuelmass_ = this->burn_->finalFuelMass();
    }

}
