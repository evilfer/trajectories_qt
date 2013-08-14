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


#include "store.h"
#include <istream>


namespace model {

    TObjectStore::TObjectStore() : objects_(), nextId_(0), free_() {
    }

    TObjectStore::~TObjectStore() {
        for (TObjectStoreMap::iterator iter = this->objects_.begin(); iter != this->objects_.end(); ++iter) {
            delete iter->second;
        }
    }


    TObjectPtr TObjectStore::create(const std::string & type) {
        int id = this->popNextId();
        TObjectPtr obj = new TObject(type, id);
        this->objects_[id] = obj;
        return obj;
    }

    int TObjectStore::popNextId() {
        if (this->free_.size() > 0) {
            int id = this->free_.back();
            this->free_.pop_back();
            return id;
        } else {
            int id = this->nextId_;
            this->nextId_ ++;
            return id;
        }
    }

    bool TObjectStore::remove(int id, Store * store) {
        if (this->objects_.find(id) != this->objects_.end()) {
            TObjectPtr obj = this->objects_[id];

            std::map<std::string, TObjectLink> & links = obj->links();
            for(std::map<std::string, TObjectLink>::iterator i = links.begin(); i != links.end(); i++) {
                TObjectLink & link = i->second;
                if (link.owned() && !link.empty()) {
                    store->remove(link.type(), link.objid());
                }
            }

            this->objects_.erase(id);
            delete obj;
            return true;
        } else {
            return false;
        }
    }

    TObjectPtr TObjectStore::find(int id) {
        return this->objects_.find(id) != this->objects_.end() ? this->objects_[id] : NULL;
    }

    void TObjectStore::findAll(TObjectList & result) {
        result.clear();
        for (TObjectStoreMap::iterator iter = this->objects_.begin(); iter != this->objects_.end(); ++iter) {
            result.push_back(iter->second);
        }
    }


    Store::Store(const TObjectModelMap & model) : model_(model), stores_(), db_() {
        this->db_.init(this->model_);
    }


    TObjectStore * Store::typeStore(const std::string & type) {
        return this->stores_.find(type) != this->stores_.end() ? & this->stores_[type] : NULL;
    }

    TObjectPtr Store::create(const std::string & type) {
        TObjectStore * store = this->typeStore(type);
        return store ? store->create(type) : NULL;
    }

    TObjectPtr Store::find(const std::string & type, int id) {
        TObjectStore * store = this->typeStore(type);
        return store ? store->find(id) : NULL;
    }

    TObjectPtr Store::find(const TObjectLink * link) {
        if (link && link->type().length() > 0 && !link->empty()) {
            return this->find(link->type(), link->objid());
        } else {
            return NULL;
        }
    }

    void Store::findAll(const std::string & type, TObjectList & list) {
        TObjectStore * store = this->typeStore(type);
        if (store) {
            store->findAll(list);
        }
    }

    bool Store::remove(const std::string & type, int id) {
        TObjectStore * store = this->typeStore(type);
        return store ? store->remove(id, this) : false;
    }

}
