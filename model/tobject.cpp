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

#include "tobject.h"


namespace model {

    const std::string TObject::DEFAULT_STRING = "";

    TObject::TObject() :
        type_(), id_(-1), ints_(), strings_(), doubles_() {
    }

    TObject::~TObject() {

    }

    void TObject::pInt(const std::string & property, int value) {
        this->ints_[property] = value;
    }

    void TObject::pDouble(const std::string & property, double value) {
        this->doubles_[property] = value;
    }

    void TObject::pString(const std::string & property, const std::string & value) {
        this->strings_[property] = value;
    }

    void TObject::pLink(const std::string & property, const std::string & type, int value) {
        this->links_[property].type_id(type, value);
    }

    void TObject::pLink(const std::string & property, const std::string & type_id) {
        this->links_[property].type_id(type_id);
    }

    int TObject::pInt(const std::string & property) const {
        std::map<std::string, int>::const_iterator i = this->ints_.find(property);
        return i == this->ints_.end() ? 0 : i->second;
    }

    double TObject::pDouble(const std::string & property) const {
        std::map<std::string, double>::const_iterator i = this->doubles_.find(property);
        return i == this->doubles_.end() ? 0 : i->second;
    }

    const std::string & TObject::pString(const std::string & property) const {
        std::map<std::string, std::string>::const_iterator i = this->strings_.find(property);
        return i == this->strings_.end() ? TObject::DEFAULT_STRING : i->second;
    }

    const TObjectLink * TObject::pLink(const std::string & property) const {
        std::map<std::string, TObjectLink>::const_iterator i = this->links_.find(property);
        return i == this->links_.end() ? NULL : &i->second;
    }

    void TObject::clearInt(const std::string & property) {
        this->ints_.erase(property);
    }

    void TObject::clearDouble(const std::string & property) {
        this->doubles_.erase(property);
    }

    void TObject::clearString(const std::string & property) {
        this->strings_.erase(property);
    }

    void TObject::clearLink(const std::string & property) {
        if (this->links_.find(property) != this->links_.end()) {
            this->links_[property].clear();
        }
    }

    bool TObject::emptyInt(const std::string & property) const {
        return this->ints_.find(property) == this->ints_.end();
    }

    bool TObject::emptyDouble(const std::string & property) const {
        return this->doubles_.find(property) == this->doubles_.end();
    }

    bool TObject::emptyString(const std::string & property) const {
        return this->strings_.find(property) == this->strings_.end();
    }

    bool TObject::emptyLink(const std::string & property) const {
        if (this->strings_.find(property) == this->strings_.end()) {
            return true;
        } else {
            return this->strings_.find(property)->second.empty();
        }
    }

}


