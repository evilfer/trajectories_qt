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

#include "trajectories.h"
#include "documentmanager.h"

#include "simulator/ephemerides/spiceposition.h"

Trajectories::Trajectories() : solarSystemManager_m(NULL) {
    ephemerides::SpicePosition::init();
    this->solarSystemManager_m = new SolarSystemStateManager();
}

Trajectories::~Trajectories() {
    delete this->solarSystemManager_m;
}


void Trajectories::processCall(QString & op, QVariantMap & data, QVariantMap &result) {

    if (op == "list") {
        DocumentManager::listDocuments(data, result);
    } else if (op == "load") {
        DocumentManager::loadDocument(data, result);
    } else if (op == "save") {
        DocumentManager::saveDocument(data, result);
    } else if (op == "loadsolarsystem") {
        solarSystemManager_m->solarSystemBodies(data, result);
    } else if (op == "solarsystemstate") {
        solarSystemManager_m->solarSystemState(data, result);
    } else if (op == "validtimerange") {
        solarSystemManager_m->timeInterval(data, result);
    }

}

