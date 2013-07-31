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

#ifndef EPHEMERIDES_BODYCONSTANTS_H
#define EPHEMERIDES_BODYCONSTANTS_H

#include <string>
#include <map>
#include <vector>


namespace ephemerides {

typedef int BodyIndex;
typedef int BodyId;


class BodyConstants {
public:
    static const BodyId SUN_ID;
    static const BodyId PLANET_CODE;

protected:
    BodyId m_id;
    BodyId m_baricenter;
    BodyId m_code;
    BodyId m_parent;
    std::string m_name;
    double m_radius;
    double m_gm; // km
    double m_mass;
    double m_interpolategap;

public:
    BodyConstants();
    BodyConstants(BodyId id, const std::string & name, double radius, double gm, double interpolategap);
    BodyConstants(const BodyConstants & other);
    BodyConstants(const BodyConstants * other);

    inline BodyId id() const {return m_id;}
    inline BodyId baricenter() const {return m_baricenter;}
    inline BodyId code() const {return m_code;}
    inline BodyId parent() const {return m_parent;}
    inline const std::string & name() const {return m_name;}
    inline double mass() const {return m_mass;}
    inline double gm() const {return m_gm;}
    inline double radius() const {return m_radius;}
    inline double gap() const {return m_interpolategap;}
};

typedef std::map<BodyIndex, BodyConstants*> BodyConstantsIdMap;
typedef std::map<std::string, BodyConstants*> BodyConstantsNameMap;
typedef std::vector<BodyConstants*> BodyConstantsVector;

typedef BodyConstantsVector::const_iterator BodyConstantsConstIterator;

class BodyConstantsList {
    BodyConstantsVector m_vector;
    BodyConstantsIdMap m_idmap;
    BodyConstantsNameMap m_namemap;

public:
    void addBody(BodyConstants * body);

    const BodyConstants * get(const std::string &name) const;
    const BodyConstants * get(BodyId id) const;

    inline const BodyConstants * operator[] (BodyId id) const {return get(id);}
    inline const BodyConstants * operator[] (const std::string & name) const {return get(name);}

    inline BodyConstantsConstIterator begin() const {return m_vector.begin();}
    inline BodyConstantsConstIterator end() const {return m_vector.end();}

    inline int size() const {return m_vector.size();}
};



struct EphemeridesInterval {
    double a, b;
    EphemeridesInterval() : a(0), b(0) {}
};

typedef std::map<BodyId, EphemeridesInterval> EphemeridesIntervalMap;

}

#endif // BODYCONSTANTS_H
