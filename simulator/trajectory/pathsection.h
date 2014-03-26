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


#ifndef TRAJECTORY_PATHSECTION_H
#define TRAJECTORY_PATHSECTION_H

#include <map>
#include <string>
#include "trajectorydata.h"
#include "world/ship.h"

namespace trajectory {

typedef std::string SectionId;
typedef std::vector<SectionId> SectionIdList;

class PathSection {
    SectionId id_;
    PathPosition from_;
    PathPosition to_;
    world::ShipSystemsState systemState_;
    bool multipoint_;

public:
    PathSection();

    void init(SectionId id, PathPosition start, const world::Ship * ship);
    void setLast(PathPosition last);

    bool belongs(PathPosition point);
    bool multipoint() const {return this->multipoint_;}

    PathPosition from() const {return this->from_;}
    PathPosition to() const {return this->to_;}

    int length() const {return this->to_ - this->from_;}
};

}

#endif // PATHSECTION_H
