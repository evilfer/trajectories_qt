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

#ifndef WORLD_BURN_H
#define WORLD_BURN_H

namespace world {
    class Burn {

        bool active_;
        double initialFuelMass_;
        double initialTotalMass_;
        double thrust_;
        double ve_;
        double startTime_;
        double defTime_;
        double endTime_;
        double dv_;
        double direction_[3];
        double duration_;
        double maxStep_;
        double finalFuelMass_;
        bool enoughFuel_;

        double alreadyBurnedPortion_;
        double stepAcc_[3];

    public:
        Burn();

        void calculateBurn(const double *dv, double burnTime, double shipmass, double initialfuelmass, double thrust, double ve);
        void startBurn();
        void computeBurnStep(double et);
        void delayUntil(double newBurnTime);
        void stopBurn();
        bool burning() const {return this->active_;}

        double initialFuelMass() const {return this->initialFuelMass_;}
        double initialTotalMass() const {return this->initialTotalMass_;}
        double startTime() const {return this->startTime_;}
        double defTime() const {return this->defTime_;}
        double endTime() const {return this->endTime_;}
        double dv() const {return this->dv_;}
        const double * direction() const {return this->direction_;}
        double duration() const {return this->duration_;}
        double maxStep() const {return this->maxStep_;}
        double finalFuelMass() const {return this->finalFuelMass_;}
        bool enoughFuel() const {return this->enoughFuel_;}

        const double * stepAcc() const {return this->stepAcc_;}

    };


}

#endif // BURN_H
