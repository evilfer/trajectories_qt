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

#ifndef WORLD_INTERPOLATOR_H
#define WORLD_INTERPOLATOR_H

#include "ephemerides/bodyconstants.h"

namespace world {

class Interpolator {
    ephemerides::BodyId body_;
    double gap_;
    double igap_;
    int index_;

    double a_[3], b_[3], c_[3];
    
//    double getIPoints(double et);
//    void interpolate(double et, Vector3 *pos, Vector3 *vel);
    double interpolate2GetPoints(double et);

public:
    Interpolator(ephemerides::BodyId body, double gap);
    virtual ~Interpolator();
    
    void interpolate2(double et, double *pos, double *vel);
};


}

#endif
