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


#ifndef WORLD_ORBIT_H
#define WORLD_ORBIT_H

#include "../tmath/vectormath.h"
#include "body.h"
#include <vector>

namespace world {

class Orbit {
  double cpos_[3], smx_[3], smy_[3];
    double opos_[3], ovel_[3];
    double gm_;

    bool isEllipse_;

    double h_[3];
    double n_[3];
    double nmod_;
    double nmod_ecc_;
    double inclination_;
    double ecc_;
    double eccv_[3];
    double recc_;
    double ascnodelon_;
    double perarg_;
    double v_;
    double eccano_;
    double meanano_;
    double radius_;
    double energy_;
    double majoraxis_;
    double semimajor_;
    double periapsis_;
    double apoapsis_;

	void calculate();
	void setOrbitAxis();

public:
    void set(const Body * centralobj, const Object * orbiter);
    void set(const Object * centralobj, double gm, const Object * orbiter);
    void set(const double * cbpos, const double * cbvel, double gm, const double * pos, const double * vel);

    const double * semimajorX() const {return this->smx_;}
    const double * semimajorY() const {return this->smy_;}
    const double * focus() const {return this->cpos_;}
	
    bool elliptic() {return this->isEllipse_;}
    double ascNodeLon() const {return this->ascnodelon_;}
    double perArg() const {return this->perarg_;}

    double eccentricity() const {return this->ecc_;}
    double inclination() const {return this->inclination_;}
    double periapsis() const {return this->periapsis_;}
    double apoapsis() const {return this->apoapsis_;}
    double radius() const {return this->radius_;}
    double eccentricAnomaly() const {return this->eccano_;}
    double trueAnomaly() const {return this->v_;}

    void calculateOrbitPosition(double angle, double *result) const;
    void calculateGlobalPosition(double angle, double *result) const;
};

}

#endif
