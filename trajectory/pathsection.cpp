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

#include "pathsection.h"

namespace trajectory {

  PathSection::PathSection(std::string key, PathPosition point) :
    key_(key), from_(point), to_(point)
  {
    this->multipoint_ = false;
  }

  PathSection::PathSection(std::string key, PathPosition from, PathPosition to) :
    key_(key), from_(from), to_(to)
  {
    this->multipoint_ = this->to_ > this->from_;

  }

  bool PathSection::belongs(PathPosition point) {
    return point >= this->from_ && point <= this->to_;
  }

}
