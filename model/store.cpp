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


    Store::Store(const TObjectModelMap & model) : stores_(), db_(model) {
        std::map<std::string, int> ids;

        this->db_.getNextIds(ids);

        for (TObjectModelMap::const_iterator i = model.begin(); i != model.end(); i++) {
            int nextid = ids.find(i->first) != ids.end() ? ids[i->first] : 1;
            this->stores_[i->first] = TObjectStore{i->second, TObjectStoreMap(), false, nextid};
        }

    }

    Store::~Store() {
        for (TypeStoreMap::iterator i = this->stores_.begin(); i != this->stores_.end(); i++) {
            for (TObjectStoreMap::iterator j = i->second.objects_.begin(); j != i->second.objects_.end(); j++) {
                delete j->second;
            }
        }
    }



    TObjectStore * Store::typeStore(const std::string & type) {
        return this->stores_.find(type) != this->stores_.end() ? & this->stores_[type] : NULL;
    }

    int Store::newId(const std::string & type) {
        TypeStoreMap::iterator storeIter = this->stores_.find(type);
        if (storeIter == this->stores_.end()) {
            return -1;
        }

        TObjectStore & store = storeIter->second;
        if (false && store.model.solid) {

        } else {
            int id = store.nextTransientId_;
            store.nextTransientId_++;
            return id;
        }
    }

    bool Store::add(TObjectPtr obj) {
        TypeStoreMap::iterator storeIter = this->stores_.find(obj->type());
        if (storeIter == this->stores_.end()) {
            return false;
        }

        TObjectStore & store = storeIter->second;
        if (store.model.solid) {
            this->db_.insertObject(obj);
        }

        store.objects_[obj->id()] = obj;
        return true;
    }

    TObjectPtr Store::find(const std::string & type, int id) {
        TypeStoreMap::iterator storeIter = this->stores_.find(type);
        if (storeIter == this->stores_.end()) {
            return NULL;
        }

        TObjectStore & store = storeIter->second;

        TObjectStoreMap::iterator objIter = store.objects_.find(id);
        if (objIter == store.objects_.end()) {
            return NULL;
        }

        return objIter->second;
    }

    TObjectPtr Store::find(const model::TObjectLink * link) {
        if (link && link->type().length() > 0 && !link->empty()) {
            return this->find(link->type(), link->objid());
        } else {
            return NULL;
        }
    }

    void Store::findAll(const std::string & type, TObjectList & result) {
        result.clear();

        TypeStoreMap::iterator storeIter = this->stores_.find(type);
        if (storeIter == this->stores_.end()) {
            return;
        }

        TObjectStore & store = storeIter->second;
        for (TObjectStoreMap::iterator iter = store.objects_.begin(); iter != store.objects_.end(); ++iter) {
            result.push_back(iter->second);
        }
    }

    bool Store::remove(const std::string & type, int id) {
        TypeStoreMap::iterator storeIter = this->stores_.find(type);
        if (storeIter == this->stores_.end()) {
            return false;
        }

        TObjectStore & store = storeIter->second;

        TObjectStoreMap::iterator objIter = store.objects_.find(id);
        if (objIter == store.objects_.end()) {
            return false;
        }

        TObjectPtr obj = objIter->second;

        store.objects_.erase(id);



        std::map<std::string, TObjectLink> & links = obj->links();
        for(std::map<std::string, TObjectLink>::iterator i = links.begin(); i != links.end(); i++) {
            TObjectLink & link = i->second;
            if (store.model.params[i->first] == TOBJECT_PARAM_OWNEDLINK && !link.empty()) {
                this->remove(link.type(), link.objid());
            }
        }

        delete obj;
        return true;
    }

    const TObjectModel * Store::getModel(const std::string & type) const {
        TypeStoreMap::const_iterator i = this->stores_.find(type);
        return i != this->stores_.end() ?  & i->second.model : NULL;
    }


}
