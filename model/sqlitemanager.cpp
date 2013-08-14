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


#include "sqlitemanager.h"
#include <fstream>
#include <sstream>

namespace model {

    SQLiteManager::SQLiteManager() {
    }

    void SQLiteManager::init(const TObjectModelMap & models) {
        int rc = sqlite3_open("../simulations/r1.sqlite3", &this->db_);
        if (rc) {
            std::cout << "Can't open database: " << sqlite3_errmsg(this->db_) << std::endl;
            return;
        }

        for (TObjectModelMap::const_iterator i = models.begin(); i != models.end(); i++) {
            std::stringstream buff;
            buff << std::string("CREATE TABLE IF NOT EXISTS ") << i->first << "(id INT";
            for (TObjectModelParams::const_iterator j = i->second.params.begin(); j != i->second.params.end(); j++) {
                if (j->second & TOBJECT_PARAM_LINKS) {
                    std::stringstream buff2;
                    buff2 << std::string("CREATE TABLE IF NOT EXISTS ") << i->first << "_" << j->first << " (a INT, b INT)";
                    this->exec(buff2.str());
                } else {

                buff << ", " << j->first;
                if (j->second == TOBJECT_PARAM_INT || j->second & TOBJECT_PARAM_LINK) {
                    buff << " INT";
                } else if (j->second == TOBJECT_PARAM_INT) {
                    buff << " REAL";
                } else if (j->second == TOBJECT_PARAM_STRING) {
                    buff << " STRING";
                }
                }
            }
            buff << ");";

            this->exec(buff.str());
        }

    }


    void SQLiteManager::createObject(TObjectPtr obj) {

    }

    void SQLiteManager::exec(const char *sql, int (*callback)(void*,int,char**,char**), void * firstParam) {
        char *zErrMsg = 0;
        int rc = sqlite3_exec(this->db_, sql, callback, firstParam, &zErrMsg);
        if (rc != SQLITE_OK){
            std::cout << "SQL error: " << sql << std::endl;
            sqlite3_free(zErrMsg);
        }
    }

    void SQLiteManager::exec(const std::string & sql, int (*callback)(void*,int,char**,char**), void * firstParam) {
        this->exec(sql.c_str(), callback, firstParam);
    }


}

