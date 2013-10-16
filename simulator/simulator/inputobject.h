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

#ifndef INPUTOBJECT_H
#define INPUTOBJECT_H

#include <vector>

namespace simulator {

    template<typename T>
    bool equals(const std::vector<T> & v1, const std::vector<T> & v2);



    class InputObject {
        std::vector<int> ints_;
        std::vector<double> doubles_;

    public:
        InputObject(std::vector<int> & ints, std::vector<double> doubles);
        const std::vector<int> & ints() const {return ints_;}
        const std::vector<double> & doubles() const {return doubles_;}

    };

    bool equals(const InputObject &io1, const InputObject &io2);

}

#endif // INPUTOBJECT_H
