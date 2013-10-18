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

#ifndef TRAJECTORIES_H
#define TRAJECTORIES_H

#include <map>
#include "html5bridgeviewer/cppjavascriptbridgelistener.h"

typedef std::map<int, QVariantMap> SimulationsIdMap;

class Trajectories : public bridge::CppJavascriptBridgeListener {

    SimulationsIdMap simulations_;
public:
    Trajectories();

    virtual QVariantMap processCall(QString & op, QVariantMap & data);


protected:
    void load();
    void save(const QVariantMap & simulation);
    void save(int id, const QVariantMap & simulation);

    void listSimulations(QVariantMap &result);
    void getSimulation(QVariantMap &data, QVariantMap &result);
    void createSimulation(QVariantMap & result);
    void saveSimulation(QVariantMap &data, QVariantMap &result);
};

#endif // TRAJECTORIES_H
