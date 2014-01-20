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
#include "../tmath/consts.h"
#include "../tmath/vectormath.h"
#include "../ephemerides/spiceposition.h"
#include "body.h"


namespace world {

Body::Body(const BodyConstants &body) : Object(), BodyConstants(body), Interpolator(body.id(), body.gap()), irregularOrbit_(NULL) {
    initOrbit();
}

Body::Body(const BodyConstants *body) : Object(), BodyConstants(body), Interpolator(body->id(), body->gap()), irregularOrbit_(NULL) {
    initOrbit();
}

Body::~Body() {
    if (irregularOrbit_) {
        delete irregularOrbit_;
    }
}

void Body::initOrbit() {
    if (this->id() > 699 && this->id() % 100 == 99) { // irregular orbit
        const ephemerides::EphemeridesInterval interval = ephemerides::SpicePosition::interval();
        double gap = interval.b - interval.a;
        int n = 300;
        double step = gap / n;
        this->irregularOrbit_ = new IrregularOrbit(n);
        for (int i = 0; i < n; i++) {
            double t = interval.a + i * step;
            this->update(t);
            tvector::set(this->pos(), irregularOrbit_->get(i));
        }
        return;
    }
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
