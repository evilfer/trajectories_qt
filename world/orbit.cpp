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


#include "orbit.h"
#include <math.h>
#include <iostream>

#include "tmath/vectormath.h"

namespace world {

  void Orbit::set(const double *cbpos, const double *cbvel, double gm, const double *pos, const double *vel) {
    tvector::set(cbpos, this->cpos_);

    tvector::substract(pos, cbpos, this->opos_);
    tvector::substract(vel, cbvel, this->ovel_);

    this->gm_ = gm;

    calculate();
  }

  void Orbit::set(const Object *centralobj, double gm, const Object *orbiter) {
    set(centralobj->pos(), centralobj->vel(), gm, orbiter->pos(), orbiter->vel());
  }

  void Orbit::set(const Body *centralobj, const Object *orbiter) {
    set(centralobj, centralobj->gm(), orbiter);
  }



  void Orbit::calculate() {
    /* specific relative angular momentum vector: h */
    tvector::cross(this->opos_, this->ovel_, this->h_);

    /* inclination */
    this->inclination_ = acos(h_[2] / tvector::mod(this->h_));

    /* eccentricity vector: eccv */
    tvector::cross(this->ovel_, this->h_, this->eccv_);
    tvector::scale(this->eccv_, 1./this->gm_);
    tvector::addScaled(this->eccv_, this->opos_, -1./tvector::mod(this->opos_));

    /* eccentricity */
    this->ecc_ = tvector::mod(this->eccv_);
    this->isEllipse_ = this->ecc_ < 1;

    /* vector pointing towards the ascending node: n */
    tvector::cross(tvector::Z, this->h_, this->n_);

    /*Longitude of the ascending node ascnodelon */
    this->nmod_ = tvector::mod(this->n_);

    this->ascnodelon_ = this->nmod_ == 0 ? 0. : acos(this->n_[0] / this->nmod_);
    if (this->n_[1] < 0) {
        this->ascnodelon_ = 2 * M_PI - this->ascnodelon_;
      }

    /* argument of the periapsis: perarg */
    this->nmod_ecc_ = this->nmod_ * this->ecc_;
    this->perarg_ = this->nmod_ecc_ == 0. ? 0. : acos(tvector::dot(this->n_, this->eccv_) / this->nmod_ecc_);
    if (this->eccv_[2] < 0) {
        this->perarg_ = 2 * M_PI - this->perarg_;
      }

    /* true anomaly: v */
    this->recc_ = tvector::mod(this->opos_) * this->ecc_;
    this->v_ = this->recc_ == 0 ? 0. : acos(tvector::dot(this->eccv_, this->opos_) / this->recc_);
    if (tvector::dot(this->opos_, this->ovel_) < 0) {
        this->v_ = 2 * M_PI - this->v_;
      }

    /* eccentric anomaly */
    this->eccano_ = atan(sqrt(1 - this->ecc_*this->ecc_) * sin(this->v_) / (this->ecc_ + cos(this->v_)));

    /* mean anomality */
    this->meanano_ = this->eccano_ - this->ecc_ * sin(this->eccano_);

    /* radius */
    this->radius_ = tvector::mod(this->opos_);

    /* specific orbital energy */
    this->energy_ = .5 * tvector::mod2(this->ovel_) - this->gm_ / this->radius_;

    /* semi-major axis */
    this->majoraxis_ = this->gm_ / this->energy_;
    this->semimajor_ = .5 * this->majoraxis_;
    if (this->isEllipse_) {
        this->semimajor_ = -this->semimajor_;
      }

    /* periapsis / apoapsis */
    if (this->isEllipse_) {
        this->periapsis_ = this->semimajor_ * (1 - this->ecc_);
        this->apoapsis_ = this->semimajor_ * (1 + this->ecc_);
      } else {
        this->periapsis_ = this->semimajor_ * (this->ecc_ - 1);
        this->apoapsis_ = 0;
      }

    setOrbitAxis();
  }

  void Orbit::setOrbitAxis() {
    double a = cos(this->perarg_);
    double pa = cos(this->inclination_) * sin(this->perarg_);
    double x = a * cos(this->ascnodelon_) - pa * sin(this->ascnodelon_);
    double y = a * sin(this->ascnodelon_) + pa * cos(this->ascnodelon_);
    double z = sin(this->inclination_) * sin(this->perarg_);

    tvector::set(x, y, z, this->smx_);
    tvector::unit(this->smx_);
    tvector::cross(this->h_, this->smx_, this->smy_);
    tvector::unit(this->smy_);
  }



  void Orbit::calculateOrbitPosition(double angle, double *result) {
    double cos_a = cos(angle);
    double k = 2. * this->apoapsis_ * this->periapsis_ / ((this->apoapsis_ - this->periapsis_) * cos_a + this->majoraxis_);

    double x = k * cos_a;
    double y = k * sin(angle);

    tvector::setScaled(this->smx_, x, result);
    tvector::addScaled(result, this->smy_, y);
  }

  void Orbit::calculateGlobalPosition(double angle, double *result) {
    calculateOrbitPosition(angle, result);
    tvector::add(result, this->cpos_);
  }


}


