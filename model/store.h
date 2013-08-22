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


#ifndef STORE_H
#define STORE_H


#include <string>
#include <map>
#include <vector>

#include "tobject.h"
#include "tobjectlink.h"
#include "sqlitemanager.h"

#define TOBJECT_MODEL_TYPE_INT      0
#define TOBJECT_MODEL_TYPE_DOUBLE   1
#define TOBJECT_MODEL_TYPE_STRING   2
#define TOBJECT_MODEL_TYPE_LINK     3

namespace model {

    typedef std::map<int, TObjectPtr> TObjectStoreMap;
    typedef std::vector<TObjectPtr> TObjectList;

    struct TObjectStore {
        TObjectModel model;
        TObjectStoreMap objects_;
        bool allLoaded_;
        int nextTransientId_;
    };


    typedef std::map<std::string, TObjectStore> TypeStoreMap;

    class Store {
        TypeStoreMap stores_;
        SQLiteManager db_;

    public:
        Store(const TObjectModelMap & model);
        ~Store();


        const TObjectModel * getModel(const std::string & type) const;
        int newId(const std::string & type);
        bool add(TObjectPtr obj);
        TObjectPtr find(const std::string & type, int id);

        TObjectPtr find(const TObjectLink * link);

        void findAll(const std::string & type, TObjectList & result);
        bool remove(const std::string & type, int id);


    private:
        TObjectStore * typeStore(const std::string & type);
    };

}

#endif // STORE_H
