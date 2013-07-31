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


namespace model {

    typedef TObject* TObjectPtr;
    typedef std::map<int, TObjectPtr> TObjectStoreMap;
    typedef std::vector<TObjectPtr> TObjectList;

    class TObjectStore {
        TObjectStoreMap objects_;
        int nextId_;
        std::vector<int> free_;

    public:
        TObjectStore();
        ~TObjectStore();

        TObjectPtr create(const std::string & type);
        TObjectPtr find(int id);
        void findAll(TObjectList & list);
        bool remove(int id);

    private:
        int popNextId();
    };


    typedef std::map<std::string, TObjectStore> TypeStoreMap;

    class Store {

        TypeStoreMap stores_;

    public:
        Store();


        TObjectPtr create(const std::string & type);
        TObjectPtr find(const std::string & type, int id);
        void findAll(const std::string & type, TObjectList & list);
        bool remove(const std::string & type, int id);

    private:
        TObjectStore & typeStore(const std::string & type);

    };

}

#endif // STORE_H
