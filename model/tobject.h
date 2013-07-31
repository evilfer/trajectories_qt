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

namespace model {

    class TObject {

        std::string type_;
        int id_;

        std::map<std::string, int> ints_;
        std::map<std::string, std::string> strings_;
        std::map<std::string, double> doubles_;

    public:
        TObject(const std::string & type, int id);

        void pInt(const std::string & property, int value);
        void pDouble(const std::string & property, double value);
        void pString(const std::string & property, const std::string & value);

        int pInt(const std::string & property) const;
        double pDouble(const std::string & property) const;
        std::string pString(const std::string & property) const;

        void clearInt(const std::string & property);
        void clearDouble(const std::string & property);
        void clearString(const std::string & property);

        bool emptyInt(const std::string & property) const;
        bool emptyDouble(const std::string & property) const;
        bool emptyString(const std::string & property) const;
    };

}

#endif // TOBJECT_H
