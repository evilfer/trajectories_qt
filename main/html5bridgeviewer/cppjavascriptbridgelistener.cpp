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

#include "cppjavascriptbridgelistener.h"
#include "cppjavascriptbridge.h"

namespace bridge {

    CppJavascriptBridgeListener::CppJavascriptBridgeListener() : bridge_(NULL) {
    }

    void CppJavascriptBridgeListener::setBridge(CppJavascriptBridge *bridge) {
        this->bridge_ = bridge;
    }

    void CppJavascriptBridgeListener::makeCall(QString &op, QVariantMap &data) {
        if (this->bridge_) {
            this->bridge_->makeCall(op, data);
        }
    }

    void CppJavascriptBridgeListener::makeCall(QString &op, QVariantList &data) {
        if (this->bridge_) {
            this->bridge_->makeCall(op, data);
        }
    }

}
