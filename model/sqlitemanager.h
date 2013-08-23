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

#include "tobject.h"
#include <map>


namespace model {

    namespace sqlqueries {

        struct SubTypeQueries {
            std::string update;
            std::string select;
        };

        typedef std::map<std::string, SubTypeQueries> SubTypeQueriesMap;

        struct TypeQueries {
            std::string insert;
            std::string update;
            std::string remove;
            std::string select;
            std::string selectall;
            SubTypeQueriesMap subqueries;
        };

        typedef std::map<std::string, TypeQueries> TypeQueriesMap;

    }

    class SQLiteManager {
        TObjectModelMap model_;
        sqlite3 *db_;
        sqlqueries::TypeQueriesMap queries_;

    public:
        SQLiteManager(const TObjectModelMap & model);

        void getNextIds(std::map<std::string, int> ids);

        void insertObject(TObjectPtr obj);
        void updateObject(TObjectPtr obj);
        void deleteObject(TObjectPtr obj);
        void deleteObject(const std::string & type, int id);

        TObjectPtr loadObject(const std::string & type, int id);
        void loadObjects(const std::string & type);

    private:
        void init(const TObjectModelMap & model);

        void exec(const std::string & sql, int (*callback)(void*,int,char**,char**) = NULL, void * firstParam = NULL);
        void exec(const char *sql, int (*callback)(void*,int,char**,char**) = NULL, void * firstParam = NULL);

        int bindParams(const TObjectPtr obj, sqlite3_stmt * stmt, int index);
        int loadParams(TObjectPtr obj, sqlite3_stmt * stmt);
    };

}

#endif // SQLITEMANAGER_H
