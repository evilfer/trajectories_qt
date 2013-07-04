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

#include <algorithm>
#include "tmath/consts.h"
#include "ephemerides/spiceposition.h"
#include "body.h"


namespace world {

Body::Body(const BodyConstants &body) : Object(), BodyConstants(body), Interpolator(body.id(), body.gap()){
}

Body::Body(const BodyConstants *body) : Object(), BodyConstants(body), Interpolator(body->id(), body->gap()){
}

void Body::update(double et) {
    interpolate2(et, this->pos_, this->vel_);
}

Body * BodyList::get(const std::string &name) {
    std::string str(name);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return this->namemap_[str];
}

Body * BodyList::get(ephemerides::BodyId id) {
    return this->idmap_[id];
}

const Body *BodyList::get(const std::string &name) const {
    std::string str(name);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return this->namemap_.at(str);
}

const Body *BodyList::get(ephemerides::BodyId id) const {
    return this->idmap_.at(id);
}

void BodyList::updateAll(double et) {
    for (BodyVector::iterator i = this->vector_.begin(); i != this->vector_.end(); i++) {
        (*i)->update(et);
    }
}

void BodyList::addBody(Body *body) {
    this->vector_.push_back(body);
    this->idmap_[body->id()] = body;

    std::string str(body->name());
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    this->namemap_[str] = body;
}



}
