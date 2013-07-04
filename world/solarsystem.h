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

#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "body.h"
#include "planetsystem.h"

namespace world {


class SolarSystem {

    Body * m_sun;
    PlanetSystemList m_planets;
    BodyList r_bodies;

public:
    static bool caseInsensitiveStringCompare(const std::string& str1, const std::string& str2);

    SolarSystem();
    virtual ~SolarSystem();

    void setSun(const ephemerides::BodyConstants * body);
    void addPlanetSystem(PlanetSystem * ps);

    void wakeUpAllSystems();
    void setAwakeSystem(PlanetSystem *ps);

    inline Body * sun() const {return m_sun;}
    inline PlanetSystemList & planets() {return m_planets;}
    void update(double et);

    const Body * body(ephemerides::BodyId bi) {return r_bodies[bi];}
    Body * body(ephemerides::BodyId bi, double et);
    ephemerides::BodyConstants * bodyConstants(ephemerides::BodyId id) {return r_bodies.get(id);}
    ephemerides::BodyConstants * bodyConstants(const std::string & name) {return r_bodies.get(name);}
};


}

#endif // SOLARSYSTEM_H
