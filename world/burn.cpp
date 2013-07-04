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

#include "burn.h"
#include "tmath/vectormath.h"
#include <cmath>

namespace world {

    Burn::Burn() {
        this->active_ = false;
    }

    void Burn::calculateBurn(const double *dv, double burnTime, double shipmass, double initialfuelmass, double thrust, double ve) {
        this->dv_ = tvector::unit(dv, this->direction_);
        this->initialFuelMass_ = initialfuelmass;
        this->initialTotalMass_ = shipmass + initialfuelmass;
        this->thrust_ = thrust;
        this->ve_ = ve;

        double ve_thrust = ve / thrust;
        double dv_ve = this->dv_ / ve;
        double fuelconsumed = this->initialTotalMass_ * (1 - exp(-dv_ve));
        double halfAccDuration = this->initialTotalMass_ * ve_thrust * (1 - exp(-.5 * dv_ve));

        this->defTime_ = burnTime;
        this->startTime_ = burnTime - halfAccDuration;

        this->enoughFuel_ = fuelconsumed <= this->initialFuelMass_;
        if (this->enoughFuel_) {
            this->finalFuelMass_ = this->initialFuelMass_ - fuelconsumed;
        } else {
            fuelconsumed = this->initialFuelMass_;
            this->finalFuelMass_ = 0;
        }

        this->duration_ = fuelconsumed * ve_thrust;
        this->maxStep_ = 001 * this->duration_;
        this->endTime_ = this->startTime_ + this->duration_;
    }


    void Burn::delayUntil(double newBurnTime) {
        double delay = newBurnTime - this->startTime_;
        this->startTime_ = newBurnTime;
        this->endTime_ += delay;
    }

    void Burn::startBurn() {
        this->active_ = true;
        this->alreadyBurnedPortion_ = 0;
    }

    void Burn::stopBurn() {
        this->active_ = false;
    }


    void Burn::computeBurnStep(double et) {
    //    double portion = log(m_initialTotalMass/(m_initialTotalMass - thrust * (et - m_startTime) / ve)) * ve / m_dv;
        double portion = log(this->initialTotalMass_/(this->initialTotalMass_ - this->thrust_ * (et - this->startTime_) / this->ve_)) * this->ve_;
        tvector::setScaled(this->direction_, portion - this->alreadyBurnedPortion_, this->stepAcc_);
        this->alreadyBurnedPortion_ = portion;
    }


}
