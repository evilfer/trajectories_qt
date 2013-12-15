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

#include "bodyconstants.h"
#include "../tmath/consts.h"
#include <algorithm>

namespace ephemerides {

    const BodyId BodyConstants::SUN_ID(10);
    const BodyId BodyConstants::PLANET_CODE(99);


    BodyConstants::BodyConstants() :
        m_id(-1), m_baricenter(0), m_code(0), m_parent(0), m_name(), m_radius(), m_gm(), m_mass(), m_interpolategap() {
    }

    BodyConstants::BodyConstants(BodyId id, const std::string & name, double radius, double gm, double interpolategap) :
        m_id(id), m_baricenter(0), m_code(id), m_parent(0), m_name(name), m_radius(radius), m_gm(gm), m_mass(gm/G), m_interpolategap(interpolategap) {
        if (id != BodyConstants::SUN_ID) {
            m_code = id % 100;
            m_baricenter = id / 100;

            if (m_code == BodyConstants::PLANET_CODE || id < 10) {
                m_parent = BodyConstants::SUN_ID;
            } else {
                m_parent = 100 * (id/100) + BodyConstants::PLANET_CODE;
            }
        }
    }

    BodyConstants::BodyConstants(const BodyConstants &other) :
        m_id(other.m_id), m_baricenter(other.m_baricenter), m_code(other.m_code), m_parent(other.m_parent), m_name(other.m_name), m_radius(other.m_radius), m_gm(other.m_gm), m_mass(other.m_mass), m_interpolategap(other.m_interpolategap) {
    }

    BodyConstants::BodyConstants(const BodyConstants *other) :
        m_id(other->m_id), m_baricenter(other->m_baricenter), m_code(other->m_code), m_parent(other->m_parent), m_name(other->m_name), m_radius(other->m_radius), m_gm(other->m_gm), m_mass(other->m_mass), m_interpolategap(other->m_interpolategap) {
    }




    const BodyConstants * BodyConstantsList::get(const std::string &name) const {
        std::string str(name);
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return m_namemap.find(str) != m_namemap.end() ? m_namemap.at(str) : 0;
    }

    const BodyConstants * BodyConstantsList::get(BodyId id) const {
        return m_idmap.find(id) != m_idmap.end() ? m_idmap.at(id) : 0;
    }

    void BodyConstantsList::addBody(BodyConstants *body) {
        m_vector.push_back(body);
        m_idmap[body->id()] = body;

        std::string str(body->name());
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        m_namemap[str] = body;
    }

    bool EphemeridesInterval::putInRange(double &time) const {
        if (time < a) {
            time = a;
            return true;
        } else if (time > b) {
            time = b;
            return true;
        }

        return false;
    }


}
