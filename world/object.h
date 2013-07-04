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


#pragma once

namespace world {

class Object {

protected:
  double pos_[3], vel_[3];

public:
    Object();
    virtual ~Object();
    
    inline double * pos() {return pos_;}
    inline double * vel() {return vel_;}

    inline const double * pos() const {return pos_;}
    inline const double * vel() const {return vel_;}
};

}

