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



#ifndef WORLD_BODY_H
#define WORLD_BODY_H

#include <vector>
#include <map>
#include "../ephemerides/bodyconstants.h"
#include "object.h"
#include "interpolator.h"
#include "irregularorbit.h"


#include <string>

namespace world {

class Body : public Object, public ephemerides::BodyConstants, public Interpolator {
    IrregularOrbit *irregularOrbit_;

    void initOrbit();
public:
    Body(const BodyConstants * body);
    Body(const BodyConstants & body);
    ~Body();
    void update(double et);

    inline bool hasIrregularOrbit() const {return irregularOrbit_ != NULL;}
    inline const IrregularOrbit * irregularOrbit() const {return irregularOrbit_;}
};

typedef std::map<ephemerides::BodyIndex, Body*> BodyIdMap;
typedef std::map<std::string, Body*> BodyNameMap;
typedef std::vector<Body*> BodyVector;

typedef BodyVector::const_iterator BodyConstIterator;

class BodyList {
    BodyVector vector_;
    BodyIdMap idmap_;
    BodyNameMap namemap_;

public:
    void addBody(Body * body);

    bool exists(const std::string &name);
    Body * get(const std::string &name);
    Body * get(ephemerides::BodyId id);
    const Body * get(const std::string &name) const;
    const Body * get(ephemerides::BodyId id) const;

    inline Body * operator[] (ephemerides::BodyId id) {return this->get(id);}
    inline Body * operator[] (const std::string & name) {return this->get(name);}

    inline const BodyVector& vector() const {return vector_;}

    void updateAll(double et);

    inline BodyConstIterator begin() const {return this->vector_.begin();}
    inline BodyConstIterator end() const {return this->vector_.end();}
};


}

#endif
