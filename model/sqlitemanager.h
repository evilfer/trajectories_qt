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


#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <sqlite3.h>
#include <iostream>

#include "tobject.h"

namespace model {

    class SQLiteManager {
        sqlite3 *db_;

    public:
        SQLiteManager();

        void init(const TObjectModelMap & models, std::map<std::string, int> ids);

        void createObject(TObjectPtr obj);

    private:
        void exec(const std::string & sql, int (*callback)(void*,int,char**,char**) = NULL, void * firstParam = NULL);
        void exec(const char *sql, int (*callback)(void*,int,char**,char**) = NULL, void * firstParam = NULL);

    };

}

#endif // SQLITEMANAGER_H
