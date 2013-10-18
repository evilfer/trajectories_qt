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
#include "serializer.h"

#include <QDirIterator>

Trajectories::Trajectories() : simulations_() {
    load();
}



void Trajectories::load() {
    QDirIterator dirIt("../simulations");
    while (dirIt.hasNext()) {
        dirIt.next();
        QFileInfo info = QFileInfo(dirIt.filePath());
        if (info.isFile() && info.suffix() == "xml") {
            bool ok;
            int id = info.baseName().toInt(&ok);
            if (ok && id > 0) {
                QFile file(dirIt.filePath());
                QVariantMap simulation = Serializer::load(file);
                simulations_[id] = simulation;
            }
        }
    }
}

void Trajectories::save(const QVariantMap & simulation) {
    bool ok;
    int id = simulation["metadata"].toMap()["id"].toInt(&ok);
    if (ok && id > 0) {
        save(id, simulation);
    }
}

void Trajectories::save(int id, const QVariantMap & simulation) {
    simulations_[id] = simulation;
    QFile file("../simulations/" + QString::number(id) + ".xml");
    Serializer::save(file, "simulation", simulation);
}



QVariantMap Trajectories::processCall(QString & op, QVariantMap & data) {
    QVariantMap result;

    if (op == "simulation_list") {
        this->listSimulations(result);
    } else if (op == "get_simulation") {
        this->getSimulation(data, result);
    } else if (op == "create_simulation") {
        this->createSimulation(result);
    } else if (op == "save_simulation") {
        this->saveSimulation(data, result);
    }

    return result;
}


void Trajectories::listSimulations(QVariantMap &result) {
    QVariantList list;

    for(SimulationsIdMap::iterator it = simulations_.begin(); it != simulations_.end(); it++) {
        list.append(it->second["metadata"].toMap());
    }

    result["list"] = list;
}

void Trajectories::createSimulation(QVariantMap & result) {

    int id = 1;
    for(SimulationsIdMap::iterator it = simulations_.begin(); it != simulations_.end(); it++) {
        int simId = it->second["metadata"].toMap()["id"].toInt();
        if (simId >= id) {
            id = simId + 1;
        }
    }

    QVariantMap simulation;

    QVariantMap metadata;
    metadata["id"] = id;
    metadata["title"] = "New simulation";
    metadata["description"] = "";
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

    save(id, simulation);

    listSimulations(result);
}

void Trajectories::getSimulation(QVariantMap &data, QVariantMap &result) {
    int id = data["id"].toInt();

    result["ok"] = true;

    QVariantMap simulation = simulations_[id];
    result["simulation"] = simulation;
}

void Trajectories::saveSimulation(QVariantMap &data, QVariantMap &result) {
    bool ok;
    int id = data["metadata"].toMap()["id"].toInt(&ok);

    if (ok && id > 0) {
        save(id, data);
    }

    result["ok"] = true;
}
