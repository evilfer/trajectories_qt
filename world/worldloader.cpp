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



#include "worldloader.h"
#include "solarsystem.h"
#include "../ephemerides/spiceposition.h"

namespace world {

  SolarSystem *WorldLoader::loadSolarSystem() {
    std::map<int, PlanetSystem*> pss;

    SolarSystem *system = new SolarSystem();

    const ephemerides::BodyConstantsList & bodies = ephemerides::SpicePosition::bodies();
    for (ephemerides::BodyConstantsConstIterator it = bodies.begin(); it != bodies.end(); it++) {
        const ephemerides::BodyConstants * b = *it;
        if (b->id() == ephemerides::BodyConstants::SUN_ID) {
            system->setSun(b);
          } else {
            PlanetSystem * ps = pss[b->baricenter()];
            if (!ps) ps = pss[b->baricenter()] = new PlanetSystem();
            ps->addPlanet(b);
          }
      }


    for (std::map<int, PlanetSystem*>::iterator i = pss.begin(); i != pss.end(); i++) {
        PlanetSystem *ps = i->second;
        ps->createBarycenter();
        system->addPlanetSystem(ps);
      }

    return system;
  }

  void WorldLoader::loadBodies(BodyList &list) {
    const ephemerides::BodyConstantsList & bodies = ephemerides::SpicePosition::bodies();
    for (ephemerides::BodyConstantsConstIterator it = bodies.begin(); it != bodies.end(); it++) {
        list.addBody(new Body(*it));
      }
  }


}
