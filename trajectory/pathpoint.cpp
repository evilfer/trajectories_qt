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

#include "pathpoint.h"

namespace trajectory {

  PathPoint::PathPoint()
  {
    this->t_ = 0;
    std::fill(this->xyz_, this->xyz_+3, 0);
    std::fill(this->vxyz_, this->xyz_+3, 0);
  }

  PathPoint::PathPoint(const PathPoint &point)
  {
    this->t_ = point.t_;
    std::copy(point.xyz(), point.xyz() + 3, this->xyz_);
    std::copy(point.vxyz(), point.vxyz() + 3, this->vxyz_);
  }

}
