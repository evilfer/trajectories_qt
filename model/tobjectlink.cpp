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


#include "tobjectlink.h"

#include <sstream>

namespace model {

    TObjectLink::TObjectLink(): type_id_(), type_(), objid_() {
    }

    void TObjectLink::type(const std::string & type) {
        this->type_ = type;
        this->objid_ = "";
        this->updateTypeId();
    }

    void TObjectLink::type_id(const std::string & type, const TObjectId & id) {
        this->type_ = type;
        this->objid_ = id;
        this->updateTypeId();
    }

    void TObjectLink::type_id(const std::string & type_id) {
        std::string::size_type sep = type_id.find(':');
        if (sep != std::string::npos) {
            this->type_id_ = type_id;
            this->type_ = type_id.substr(0, sep);
            this->objid_ = atoi(type_id.substr(sep + 1).c_str());
        } else {
            this->type_id_ = "";
            this->type_ = "";
            this->objid_ = "";
        }

    }

    void TObjectLink::clear() {
        this->objid_ = "";
        this->updateTypeId();
    }

    void TObjectLink::updateTypeId() {
        if (this->empty()) {
            this->type_id_ = "";
        } else {
            std::stringstream ss;
            ss << this->type_ << ":" << this->objid_;
            this->type_id_ = ss.str();
        }
    }



}
