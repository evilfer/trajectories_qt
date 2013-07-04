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

#include "gravityfield.h"

#include <float.h>
#include <cmath>
#include "tmath/vectormath.h"

namespace world {


  GravityField::GravityField(SolarSystem *solarsystem) : solarsystem_r(solarsystem) {
  }

  GravityField::~GravityField() {

  }

  void GravityField::getAcc(const double *pos, double *acc, Body *body, PlanetSystem *owner) {
    static double v[3];
    static double d2, d, f;

    tvector::substract(body->pos(), pos, v);
    d2 = tvector::mod2(v);
    d = sqrt(d2);
    f = body->gm() / d2;
    tvector::addScaled(acc, v, f/d);

    if (d < this->distance_) {
        this->distance_ = d;
        this->closest_r = owner;
        this->closestbody_r = body;
      }

    if (f > this->force_) {
        this->force_ = f;
        this->strongest_r = owner;
        this->strongestbody_r = body;
      }
  }

  void GravityField::updateAccDistance(const double *pos, double *acc) {
    this->distance_ = DBL_MAX;
    this->force_ = -1;

    tvector::reset(acc);
    this->getAcc(pos, acc, this->solarsystem_r->sun(), 0);
    
    for (PlanetSystemList::iterator i = this->solarsystem_r->planets().begin(); i != this->solarsystem_r->planets().end(); i++) {
        PlanetSystem * ps = (*i);
        if (ps->simplemode()) {
            getAcc(pos, acc, ps->baricenter(), 0);
          } else {
            for (BodyVector::iterator j = ps->bodies().begin(); j != ps->bodies().end(); j++) {
                getAcc(pos, acc, *j, ps);
              }
          }
      }
  }

}
