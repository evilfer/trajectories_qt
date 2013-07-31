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

#include "planetsystem.h"

#include <iostream>
#include <cstdlib>

namespace world {


PlanetSystem::PlanetSystem() : m_baricenter(0), r_main(0), m_planets(), m_simplemode(false) {
}

PlanetSystem::~PlanetSystem() {
    if (m_baricenter) {
        delete m_baricenter;
    }
    for (BodyVector::iterator i = m_planets.begin(); i != m_planets.end(); i++) {
        delete (Body*) (*i);
    }
}

void PlanetSystem::addPlanet(const ephemerides::BodyConstants *body) {
    m_planets.push_back(new Body(body));
}

void PlanetSystem::createBarycenter() {
    double gm = 0;
    r_main = 0;
    if (m_planets.size() == 0) {
        std::cerr << "Planetary system with no planets!" << std::endl;
        abort();
    }

    for (BodyVector::iterator it = m_planets.begin(); it != m_planets.end(); it++) {
        gm += (*it)->gm();
        if ((*it)->code() == ephemerides::BodyConstants::PLANET_CODE) {
            r_main = *it;
        }
    }

    if (r_main == 0) {
        std::cerr << "Didn't find the main planet for planetary system " << (*m_planets.begin())->baricenter() << std::endl;
        abort();
    }

    m_baricenter = new Body(ephemerides::BodyConstants(r_main->baricenter(), std::string(r_main->name()).append(" barycenter"), 0, gm, r_main->gap()));
}

void PlanetSystem::update(double et) {
    if (m_simplemode) {
        m_baricenter->update(et);
    } else {
        for (BodyVector::iterator it = m_planets.begin(); it != m_planets.end(); it++) {
            (*it)->update(et);
        }
    }
}

}
