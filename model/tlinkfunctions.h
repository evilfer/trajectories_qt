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


#ifndef TLINKFUNCTIONS_H
#define TLINKFUNCTIONS_H

#include <string>

#include "store.h"
#include "tobject.h"
#include "tobjectlink.h"

namespace model {

    void link(TObjectPtr a, const std::string & propertyA, TObjectPtr b, const std::string & propertyB);
    void link(Store & store, const std::string & typeA, int idA, const std::string & propertyA, const std::string & typeB, int idB, const std::string & propertyB);

}

#endif // TLINKFUNCTIONS_H
