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
