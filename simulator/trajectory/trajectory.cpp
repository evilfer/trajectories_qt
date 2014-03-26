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

#include "trajectory.h"

namespace trajectory {

Trajectory::Trajectory(const world::World* world) : world_(world), data_(), sections_(), children_(), parents_() {
    this->clear();
}

void Trajectory::clear() {
    this->data_.clear();
    this->sections_.clear();
    this->children_.clear();
    this->parents_.clear();
    this->currentSection_ = "";
    this->children_[this->currentSection_] = SectionIdList();
}


void Trajectory::selectSection(SectionId section) {
    this->currentSection_ = section;
}

SectionId Trajectory::initNewSection() {
    SectionId parent = currentSection_;
    SectionId id = (currentSection_.length() > 0 ? currentSection_ + std::string(".") : std::string("")) + std::to_string(children_[currentSection_].size());
    children_[parent].push_back(id);
    parents_[id] = parent;
    sections_[id].init(id, data_.lastPoint(), world_->ship());
    currentSection_ = id;
    return id;
}

void Trajectory::savePoint() {
    this->data_.push_back(PathPoint(world_->time(), world_->ship()->pos(), world_->ship()->vel()));
}

void Trajectory::completeSection() {
    sections_[currentSection_].setLast(data_.lastPoint());
}


}
