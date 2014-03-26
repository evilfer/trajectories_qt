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


#ifndef TRAJECTORY_PATHPOINT_H
#define TRAJECTORY_PATHPOINT_H

#include <algorithm>

namespace trajectory {

    class PathPoint {
        double xyz_[3];
        double vxyz_[3];
        double t_;

        void set(double et, const double* pos, const double* vel);

    public:
        PathPoint();
        PathPoint(const PathPoint& point);
        PathPoint(double et, const double* pos, const double* vel);

        const double * xyz() const {return this->xyz_;}
        double * xyz() {return this->xyz_;}

        const double * vxyz() const {return this->vxyz_;}
        double * vxyz() {return this->vxyz_;}

        double t() const {return this->t_;}
    };

}

#endif // PATHPOINT_H
