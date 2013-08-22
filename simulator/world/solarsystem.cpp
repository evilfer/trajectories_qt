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

#include "solarsystem.h"

namespace world {


SolarSystem::SolarSystem() : m_sun(0), m_planets(), r_bodies() {
}

SolarSystem::~SolarSystem() {
    delete m_sun;
    for (PlanetSystemList::iterator i = m_planets.begin(); i != m_planets.end(); i++) {
        delete (PlanetSystem*) (*i);
    }
}

void SolarSystem::setSun(const ephemerides::BodyConstants *body) {
    m_sun = new Body(body);
}

void SolarSystem::addPlanetSystem(PlanetSystem *ps) {
    m_planets.push_back(ps);
    for (BodyVector::iterator i = ps->bodies().begin(); i != ps->bodies().end(); i++) {
        r_bodies.addBody(*i);
    }
}

void SolarSystem::wakeUpAllSystems() {
    for (PlanetSystemList::iterator it = m_planets.begin(); it != m_planets.end(); it++) {
        (*it)->set(false);
    }
}

void SolarSystem::setAwakeSystem(PlanetSystem *ps) {
    for (PlanetSystemList::iterator it = m_planets.begin(); it != m_planets.end(); it++) {
        (*it)->set(ps != (*it));
    }
}

void SolarSystem::update(double et) {
    m_sun->update(et);
    for (PlanetSystemList::iterator it = m_planets.begin(); it != m_planets.end(); it++) {
        (*it)->update(et);
    }
}

Body *SolarSystem::body(ephemerides::BodyId id, double et) {
    Body * b = r_bodies.get(id);
    b->update(et);
    return b;
}




}