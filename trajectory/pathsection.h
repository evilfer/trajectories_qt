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
