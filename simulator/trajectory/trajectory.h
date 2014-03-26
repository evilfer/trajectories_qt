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

#ifndef TRAJECTORY_TRAJECTORY_H
#define TRAJECTORY_TRAJECTORY_H

#include <map>
#include <vector>

#include "trajectorydata.h"
#include "pathsection.h"
#include "world/world.h"

namespace trajectory {

typedef std::map<SectionId, PathSection>  SectionMap;
typedef std::map<SectionId, SectionIdList> SectionChildrenMap;
typedef std::map<SectionId, SectionId> SectionParentMap;


class Trajectory {
    const world::World* world_;

    TrajectoryData data_;
    SectionMap sections_;
    SectionChildrenMap children_;
    SectionParentMap parents_;
    SectionId currentSection_;

public:
    Trajectory(const world::World *world);

    void clear();

    void savePoint();

    SectionId initNewSection();
    void completeSection();
    void selectSection(SectionId section);

    const SectionIdList& roots() const {return children_.at("");}
    const SectionMap& sections() const {return sections_;}
    const SectionIdList& children(const SectionId& parent) const {return children_.at(parent);}
};

}

#endif // TRAJECTORY_H
