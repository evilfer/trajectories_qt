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

#ifndef PATHPOINT_H
#define PATHPOINT_H

#include <algorithm>

namespace trajectory {

  class PathPoint
  {
    double xyz_[3];
    double vxyz_[3];
    double t_;
  public:
    PathPoint();
    PathPoint(const PathPoint& point);

    double x() const {return this->xyz_[0];}
    double y() const {return this->xyz_[1];}
    double z() const {return this->xyz_[2];}

    void setX(double x) {this->xyz_[0] = x;}
    void setY(double y) {this->xyz_[1] = y;}
    void setZ(double z) {this->xyz_[2] = z;}

    const double * xyz() const {return this->xyz_;}
    double * xyz() {return this->xyz_;}

    double vx() const {return this->vxyz_[0];}
    double vy() const {return this->vxyz_[1];}
    double vz() const {return this->vxyz_[2];}

    void setVX(double vx) {this->vxyz_[0] = vx;}
    void setVY(double vy) {this->vxyz_[1] = vy;}
    void setVZ(double vz) {this->vxyz_[2] = vz;}

    const double * vxyz() const {return this->vxyz_;}
    double * vxyz() {return this->vxyz_;}

    double t() const {return this->t_;}
    void setT(double t) {this->t_ = t;}
  };

}

#endif // PATHPOINT_H
