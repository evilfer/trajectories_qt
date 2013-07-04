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

#include "interpolator.h"

#include "ephemerides/spiceposition.h"
#include "tmath/vectormath.h"

#include <limits.h>
#include <cmath>

namespace world {

  Interpolator::Interpolator(ephemerides::BodyId body, double gap) : body_(body), gap_(gap), igap_(1. / gap), index_(INT_MIN) {
  }

  Interpolator::~Interpolator() {
  }


  void Interpolator::interpolate2(double et, double* pos, double* vel) {
    double dt = interpolate2GetPoints(et);
    tvector::set(this->a_, pos); // e = ps[0]
    tvector::addScaled(pos, this->b_, dt);
    tvector::set(vel, this->b_);
  }


  double Interpolator::interpolate2GetPoints(double et) {
    double findex = floor(et*this->igap_);
    int index = (int) findex;
    double time0 = findex * this->gap_;
    double dt = et - time0;

    int diff = index - this->index_;

    if (diff == 1) {
        tvector::set(this->c_, this->a_);
        ephemerides::SpicePosition::getpos(this->body_, time0 + this->gap_, this->c_);
      } else if (diff == -1) {
        tvector::set(this->a_, this->c_);
        ephemerides::SpicePosition::getpos(this->body_, time0, this->a_);
      } else if (diff != 0) {
        ephemerides::SpicePosition::getpos(this->body_, time0, this->a_);
        ephemerides::SpicePosition::getpos(this->body_, time0 + this->gap_, this->c_);
      }

    if (diff != 0) {
        tvector::substract(this->c_, this->a_, this->b_);
        tvector::scale(this->b_, this->igap_);
        this->index_ = index;
      }

    return dt;
  }


}
