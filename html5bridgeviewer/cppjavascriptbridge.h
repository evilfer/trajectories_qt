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

#ifndef CPPJAVASCRIPTBRIDGE_H
#define CPPJAVASCRIPTBRIDGE_H

#include <QObject>

#include "cppjavascriptbridgelistener.h"

#define BRIDGE_BAD      -1
#define BRIDGE_FIND     0
#define BRIDGE_FINDALL  1
#define BRIDGE_CREATE   2
#define BRIDGE_UPDATE   3
#define BRIDGE_DELETE   4
#define BRIDGE_NEWID    5

namespace bridge {

    class CppJavascriptBridge : public QObject {
        Q_OBJECT

        /* reference to not-owned listener */
        CppJavascriptBridgeListener * listener_;

    public:
        CppJavascriptBridge(CppJavascriptBridgeListener * listener);
        ~CppJavascriptBridge();
        void makeCall(QString &op, QVariantMap & data);
        void makeCall(QString &op, QVariantList & data);

    signals:
        void call_js_obj(QString op, QVariantMap data);
        void call_js_array(QString op, QVariantList data);

    public slots:
        QVariantMap call_qt_sync(QString opId, QVariantMap data);
    };

}

#endif // CPPJAVASCRIPTBRIDGE_H
