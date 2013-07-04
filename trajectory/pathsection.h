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


#ifndef PATHSECTION_H
#define PATHSECTION_H

#include <map>
#include <string>
#include "path.h"

namespace trajectory {


  class PathSection
  {
    std::string key_;
    PathPosition from_;
    PathPosition to_;
    bool multipoint_;

  public:
    PathSection(std::string key, PathPosition point);
    PathSection(std::string key, PathPosition from, PathPosition to);

    bool belongs(PathPosition point);
    bool multipoint() const {return this->multipoint_;}

    PathPosition from() const {return this->from_;}
    PathPosition to() const {return this->to_;}
  };

  typedef std::map<std::string, PathSection> PathSectionMap;

}

#endif // PATHSECTION_H
