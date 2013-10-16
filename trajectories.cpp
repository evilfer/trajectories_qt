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



Trajectories::Trajectories() {
}


QVariantMap Trajectories::processCall(QString & op, QVariantMap & data) {
    QVariantMap result;

    if (op == "simulation_list") {
        this->listSimulations(result);
    } else if (op == "get_simulation") {
        this->getSimulation(data, result);
    }

    return result;
}

void Trajectories::listSimulations(QVariantMap &result) {
    QVariantList list;

    QVariantMap item;
    item["id"] = 1;
    item["title"] = "test 1";
    list.append(item);

    result["list"] = list;
}

void Trajectories::getSimulation(QVariantMap &data, QVariantMap &result) {
    QString id = data["id"].toString();

    result["ok"] = true;

    QVariantMap simulation;

    QVariantMap metadata;
    metadata["id"] = id;
    metadata["title"] = "test 1";
    metadata["description"] = "description";
    simulation["metadata"] = metadata;

    QVariantMap config;
    config["ephemerides"] = "spice";
    simulation["config"] = config;

    QVariantMap ship;
    ship["name"] = "deltaglider";
    ship["thrust"] = 1000.;
    ship["isp"] = 50.;
    ship["mass"] = 10000.;
    ship["fuelmass"] = 20000.;
    simulation["ship"] = ship;

    result["simulation"] = simulation;
}
