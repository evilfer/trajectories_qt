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

#ifndef CPPJAVASCRIPTBRIDGELISTENER_H
#define CPPJAVASCRIPTBRIDGELISTENER_H

#include <QObject>
#include <QVariantMap>

namespace bridge {
    class CppJavascriptBridge;

    class CppJavascriptBridgeListener {

        CppJavascriptBridge * bridge_;

    public:
        CppJavascriptBridgeListener();
        void setBridge(CppJavascriptBridge * bridge);

        virtual void processCall(int op, int opId, QVariantMap & data) = 0;

    protected:
        void makeCall(int opId, bool complete, QVariantMap & data);
        void makeCall(int opId, bool complete, QVariantList & data);
    };
}


#endif // CPPJAVASCRIPTBRIDGELISTENER_H
