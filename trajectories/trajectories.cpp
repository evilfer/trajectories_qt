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

#include "simulator/world/worldloader.h"
#include "simulator/ephemerides/spiceposition.h"

Trajectories::Trajectories() {
    this->solarsystem_m = world::WorldLoader::loadSolarSystem();
    this->solarsystem_m->wakeUpAllSystems();
}

Trajectories::~Trajectories() {
    delete this->solarsystem_m;
}


QVariantMap Trajectories::processCall(QString & op, QVariantMap & data) {
    QVariantMap result;

    if (op == "list") {
        DocumentManager::listDocuments(data, result);
    } else if (op == "load") {
        DocumentManager::loadDocument(data, result);
    } else if (op == "save") {
        DocumentManager::saveDocument(data, result);
    }

    return result;
}



void Trajectories::timeInterval(QVariantMap &, QVariantMap &result) {
    const ephemerides::EphemeridesInterval & interval = ephemerides::SpicePosition::interval();
    result["a"] = interval.a;
    result["b"] = interval.b;
}

void Trajectories::solarSystemBodies(QVariantMap &data, QVariantMap &result) {

}

void Trajectories::solarSystemState(QVariantMap &data, QVariantMap &result) {
    const ephemerides::EphemeridesInterval & interval = ephemerides::SpicePosition::interval();

    bool ok;
    double time = data["time"].toDouble(&ok);

    if (ok) {
        interval.putInRange(time);
    } else {
        time = interval.a;
    }

    solarsystem_m->update(time);

    for (world::BodyConstIterator it = solarsystem_m->bodies().begin(); it != solarsystem_m->bodies().end(); it++) {
        const world::Body * body = (*it);
        QVariantMap state;

        Trajectories::vector2map(body->pos(), state, "pos");
        Trajectories::vector2map(body->vel(), state, "vel");

        result[QString::number(body->id())] = state;
    }
}

 void Trajectories::vector2map(const double* vector, QVariantMap &result, const QString &key) {
     QVariantList list;
     for (int i = 0; i < 3; i++) {
         list.append(vector[i]);
     }
     result[key] = list;
 }

