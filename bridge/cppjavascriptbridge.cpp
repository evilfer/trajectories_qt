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

#include "cppjavascriptbridge.h"
#include <iostream>

namespace bridge {

    CppJavascriptBridge::CppJavascriptBridge(CppJavascriptBridgeListener * listener) : listener_(listener) {
    }

    void CppJavascriptBridge::call_qt(int op, int opId, QVariantMap data) {
        this->listener_->processCall(op, opId, data);
    }

    QVariantMap CppJavascriptBridge::call_qt_sync(int op, QVariantMap data) {
        return this->listener_->processSyncCall(op, data);
    }

    void CppJavascriptBridge::makeCall(int op, bool complete, QVariantMap & data) {
        this->call_js(op, complete, data);
    }
}

