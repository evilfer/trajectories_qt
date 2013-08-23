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

#ifndef TOBJECTLINK_H
#define TOBJECTLINK_H

#include <string>
#include <vector>

namespace model {


    class TObjectLink {
        std::string type_id_;
        std::string type_;
        int objid_;

    public:
        TObjectLink();

        void type(const std::string & type);
        void type_id(const std::string & type_id);
        void type_id(const std::string & type, int id);

        const std::string & type() const {return this->type_;}
        int objid() const {return this->objid_;}

        void clear();
        bool empty() const {return this->objid_ < 0;}

        const std::string & toString() const {return this->type_id_;}

    private:
        void updateTypeId();
    };

    typedef std::vector<TObjectLink> TObjectLinkArray;

}


#endif // TOBJECTLINK_H
