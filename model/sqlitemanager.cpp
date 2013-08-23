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
#include <iostream>

namespace model {

    SQLiteManager::SQLiteManager(const TObjectModelMap & model) : model_(), db_(NULL), queries_() {
        this->init(model);
    }

    void SQLiteManager::init(const TObjectModelMap & model) {
        int rc = sqlite3_open("../simulations/r1.sqlite3", &this->db_);
        if (rc) {
            std::cout << "Can't open database: " << sqlite3_errmsg(this->db_) << std::endl;
            return;
        }

        for (TObjectModelMap::const_iterator i = model.begin(); i != model.end(); i++) {
            if (i->second.solid) {
                this->model_[i->first] = i->second;

                std::stringstream createQuery;
                std::stringstream insertQuery;
                std::stringstream deleteQuery;
                std::stringstream updateQuery;
                std::stringstream findQuery;
                std::stringstream allQuery;

                createQuery << "CREATE TABLE IF NOT EXISTS " << i->first << "(id INT";
                insertQuery << "INSERT INTO " << i->first << " (id";
                updateQuery << "UPDATE " << i->first << " SET ";
                deleteQuery << "DELETE FROM " << i->first << " WHERE id=?";
                findQuery << "SELECT ";
                allQuery << "SELECT * FROM " << i->first;

                bool notFirst = false;

                for (TObjectModelParams::const_iterator j = i->second.params.begin(); j != i->second.params.end(); j++) {
                    if (!(j->second & TOBJECT_PARAM_LINKS)) {
                        if (notFirst) {
                            updateQuery << ", ";
                            findQuery << ", ";
                        } else {
                            notFirst = true;
                        }
                        updateQuery << j->first << "=?";
                        findQuery << j->first;

                        insertQuery << ", " << j->first;

                        createQuery << ", " << j->first;
                        if (j->second == TOBJECT_PARAM_INT) {
                            createQuery << " INT";
                        } else if (j->second == TOBJECT_PARAM_DOUBLE) {
                            createQuery << " REAL";
                        } else if (j->second == TOBJECT_PARAM_STRING || j->second & TOBJECT_PARAM_LINK) {
                            createQuery << " STRING";
                        }
                    }
                }

                createQuery << ")";
                this->exec(createQuery.str());

                insertQuery << ") VALUES (?";
                updateQuery << " WHERE id=?";
                findQuery << " FROM " << i->first << " WHERE id=?";

                for (TObjectModelParams::const_iterator j = i->second.params.begin(); j != i->second.params.end(); j++) {
                    if (j->second & TOBJECT_PARAM_LINKS) {
                        std::stringstream subcreateQuery;
                        std::stringstream subupdateQuery;
                        std::stringstream subfindQuery;

                        subcreateQuery << "CREATE TABLE IF NOT EXISTS " << i->first << "_" << j->first << " (id INT, child STRING)";
                        this->exec(subcreateQuery.str());

                        subupdateQuery << "DELETE FROM " << i->first << "_" << j->first <<
                                          " WHERE id=?;INSERT INTO " << i-> first<< "_" << j->first << " (id, child) VALUES ";

                        subfindQuery << "SELECT child FROM " << i->first << "_" << j->first <<
                                        " WHERE id=?";

                        this->queries_[i->first].subqueries[j->first].update = subupdateQuery.str();
                        this->queries_[i->first].subqueries[j->first].select = subfindQuery.str();

                    } else {
                        insertQuery << ", ?";
                    }
                }

                insertQuery << ")";

                this->queries_[i->first].insert = insertQuery.str();
                this->queries_[i->first].update = updateQuery.str();
                this->queries_[i->first].remove = deleteQuery.str();
                this->queries_[i->first].select = findQuery.str();
                this->queries_[i->first].selectall = allQuery.str();
            }
        }
    }

    void SQLiteManager::getNextIds(std::map<std::string, int> ids) {
        ids.clear();

        for (TObjectModelMap::const_iterator i = this->model_.begin(); i != this->model_.end(); i++) {
            std::stringstream query;
            query << "SELET MAX(id) FROM " << i->first;
            std::cout << query.str() << std::endl;
        }
    }


    void SQLiteManager::insertObject(TObjectPtr obj) {
        sqlite3_stmt * stmt;
        sqlite3_prepare_v2(this->db_, this->queries_[obj->type()].insert.c_str(), -1, &stmt, NULL);

        sqlite3_bind_int(stmt, 1, obj->id());
        this->bindParams(obj, stmt, 2);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    void SQLiteManager::updateObject(TObjectPtr obj) {
        sqlite3_stmt * stmt;
        sqlite3_prepare_v2(this->db_, this->queries_[obj->type()].update.c_str(), -1, &stmt, NULL);

        int lastIndex = this->bindParams(obj, stmt, 1);
        sqlite3_bind_int(stmt, lastIndex, obj->id());

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    void SQLiteManager::deleteObject(TObjectPtr obj) {
        this->deleteObject(obj->type(), obj->id());
    }

    void SQLiteManager::deleteObject(const std::string & type, int id) {
        sqlite3_stmt * stmt;
        sqlite3_prepare_v2(this->db_, this->queries_[type].remove.c_str(), -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }


    TObjectPtr SQLiteManager::loadObject(const std::string & type, int id) {
        TObjectPtr obj = NULL;

        sqlite3_stmt * stmt;
        sqlite3_prepare_v2(this->db_, this->queries_[type].select.c_str(), -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            TObjectPtr obj = new TObject();
            obj->setType(type);
            obj->setId(id);
            this->loadParams(obj, stmt);
        }

        sqlite3_finalize(stmt);
        return obj;
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

    int SQLiteManager::bindParams(const TObjectPtr obj, sqlite3_stmt * stmt, int index) {
        TObjectModelParams &model = this->model_[obj->type()].params;

        for (TObjectModelParams::const_iterator iter = model.begin(); iter != model.end(); iter++) {
            if (iter->second == TOBJECT_PARAM_INT) {
                if (obj->emptyInt(iter->first)) {
                    sqlite3_bind_null(stmt, index);
                } else {
                    sqlite3_bind_int(stmt, index, obj->pInt(iter->first));
                }
            } else if (iter->second == TOBJECT_PARAM_DOUBLE) {
                if (obj->emptyDouble(iter->first)) {
                    sqlite3_bind_null(stmt, index);
                } else {
                    sqlite3_bind_double(stmt, index, obj->pDouble(iter->first));
                }
            } else if (iter->second == TOBJECT_PARAM_STRING) {
                sqlite3_bind_text(stmt, index, obj->pString(iter->first).c_str(), -1, SQLITE_TRANSIENT);
            } else if (iter->second & TOBJECT_PARAM_LINK) {
                const TObjectLink * link = obj->pLink(iter->first);
                if (!link || link->empty()) {
                    sqlite3_bind_null(stmt, index);
                } else {
                    sqlite3_bind_text(stmt, index, obj->pLink(iter->first)->toString().c_str(), -1, SQLITE_TRANSIENT);
                }
            }
            index++;
        }
        return index;
    }

    int SQLiteManager::loadParams(TObjectPtr obj, sqlite3_stmt * stmt) {
        TObjectModelParams &model = this->model_[obj->type()].params;

        int column = 0;

        for (TObjectModelParams::const_iterator iter = model.begin(); iter != model.end(); iter++) {
            bool isNull = sqlite3_column_type(stmt, column) == SQLITE_NULL;

            if (iter->second == TOBJECT_PARAM_INT) {
                if (isNull) {
                    obj->clearInt(iter->first);
                } else {
                    int value = sqlite3_column_int(stmt, column);
                    obj->pInt(iter->first, value);
                }
            } else if (iter->second == TOBJECT_PARAM_DOUBLE) {
                if (isNull) {
                    obj->clearDouble(iter->first);
                } else {
                    double value = sqlite3_column_double(stmt, column);
                    obj->pDouble(iter->first, value);
                }
            } else if (iter->second == TOBJECT_PARAM_STRING) {
                if (isNull) {
                    obj->clearString(iter->first);
                } else {
                    std::string value = std::string(reinterpret_cast< const char* >(sqlite3_column_text(stmt, column)));
                    obj->pString(iter->first, value);
                }
            } else if (iter->second & TOBJECT_PARAM_LINK) {
                if (isNull) {
                    obj->clearLink(iter->first);
                } else {
                    std::string value = std::string(reinterpret_cast< const char* >(sqlite3_column_text(stmt, column)));
                    obj->pLink(iter->first, value);
                }
            }

            column++;
        }
        return 0;
    }

}

