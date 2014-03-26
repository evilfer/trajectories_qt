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


#include "inputobject.h"

#include <vector>

namespace simulator {

    InputObject::InputObject(std::vector<int> & ints, std::vector<double> doubles) : ints_(), doubles_() {
        for (int i : ints) {
            ints_.push_back(i);
        }
        for (double d : doubles) {
            doubles_.push_back(d);
        }
    }

    bool equals(const InputObject &io1, const InputObject &io2) {
        return equals(io1.ints(), io1.ints()) && equals(io1.doubles(), io2.doubles());
    }

    template<typename T>
    bool equals(const std::vector<T> & v1, const std::vector<T> & v2) {
        if (v1.size() != v2.size()) {
            return false;
        } else {
            for (unsigned int i = 0; i < v1.size(); i++) {
                if (v1[i] != v2[i]) {
                    return false;
                }
            }
            return true;
        }
    }

}
