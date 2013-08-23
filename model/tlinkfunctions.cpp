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


#include "tlinkfunctions.h"


namespace model {

    void link(Store * store, TObjectPtr a, const std::string & propertyA, TObjectPtr b, const std::string & propertyB) {
        if (a && b) {
            a->pLink(propertyA, b->type(), b->id());
            b->pLink(propertyB, a->type(), a->id());
        } else if (a) {
            a->clearLink(propertyA);
        } else if (b) {
            b->clearLink(propertyB);
        }
    }

    void link(Store * store, const std::string & typeA, int idA, const std::string & propertyA, const std::string & typeB, int idB, const std::string & propertyB) {
        link(store, store->find(typeA, idA), propertyA, store->find(typeB, idB), propertyB);
    }

}
