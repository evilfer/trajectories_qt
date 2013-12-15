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

#ifndef WORLD_PLANETSYSTEM_H
#define WORLD_PLANETSYSTEM_H

#include "body.h"

namespace world {


class PlanetSystem {
    Body * m_baricenter;
    Body * r_main;
    BodyVector m_planets;
    bool m_simplemode;

public:
    PlanetSystem();
    ~PlanetSystem();

    void addPlanet(const ephemerides::BodyConstants *body);
    void createBarycenter();

    void update(double et);

    void set(bool simplemode) {m_simplemode = simplemode;}

    inline bool simplemode() {return m_simplemode;}
    inline Body * baricenter() {return m_baricenter;}
    inline Body * main() {return r_main;}
    inline BodyVector & bodies() {return m_planets;}
};

typedef std::vector<PlanetSystem*> PlanetSystemList;
typedef std::map<int, PlanetSystem*> PlanetSystemMap;

}
#endif // PLANETSYSTEM_H
