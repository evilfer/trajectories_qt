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

#ifndef TOBJECT_H
#define TOBJECT_H

#include <string>
#include <map>
#include <vector>

#include "tobjectlink.h"


#define TOBJECT_PARAM_INT           00000001
#define TOBJECT_PARAM_DOUBLE        00000002
#define TOBJECT_PARAM_STRING        00000004


namespace model {



    class TObject {

        static const std::string DEFAULT_STRING;

        std::string type_;
        TObjectId id_;

        std::map<std::string, int> ints_;
        std::map<std::string, std::string> strings_;
        std::map<std::string, double> doubles_;
        std::map<std::string, TObjectLink> links_;

    public:
        TObject();
        ~TObject();

        const std::string & type() const {return this->type_;}
        const TObjectId & id() const {return this->id_;}
        void setType(const std::string type) {this->type_ = type;}
        void setId(const TObjectId & id) {this->id_ = id;}

        void setInt(const std::string & property, int value);
        void setDouble(const std::string & property, double value);
        void setString(const std::string & property, const std::string & value);

        void setLink(const std::string & property, const std::string & type, const TObjectId & id);
        void setLink(const std::string & property, const std::string & type_id);

        int getInt(const std::string & property) const;
        double getDouble(const std::string & property) const;
        const std::string & getString(const std::string & property) const;
        const TObjectLink * getLink(const std::string & property) const;

        void clearInt(const std::string & property);
        void clearDouble(const std::string & property);
        void clearString(const std::string & property);
        void clearLink(const std::string & property);

        bool emptyInt(const std::string & property) const;
        bool emptyDouble(const std::string & property) const;
        bool emptyString(const std::string & property) const;
        bool emptyLink(const std::string & property) const;

        std::map<std::string, TObjectLink> & links() {return this->links_;}
    };

    typedef TObject* TObjectPtr;

    typedef std::map<TObjectId, TObjectPtr> TObjectIdMap;

    struct TObjectLinkModel {
        bool owned;
        bool polymorphic;
        const char * type;
        const char * id_key;
        const char * type_key;
        bool toSingleton;
    };

    typedef std::map<std::string, int> TObjectModelParams;
    typedef std::map<std::string, TObjectLinkModel> TObjectModelLinkParams;


    struct TObjectModel {
        bool solid;
        const char * plural;
        TObjectModelParams params;
        TObjectModelLinkParams links;
        TObjectModelLinkParams arrays;
    };

    typedef std::map<std::string, TObjectModel> TObjectModelMap;
}

#endif // TOBJECT_H
