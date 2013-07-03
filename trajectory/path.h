#ifndef PATH_H
#define PATH_H

#include <deque>
#include "pathpoint.h"

namespace trajectory {

  typedef std::deque<PathPoint>::const_iterator PathPosition;

  class Path : std::deque<PathPoint>
  {
  public:
    Path();

    PathPosition startSection(const PathPoint &startPoint);
    void save(const PathPoint& point) {this->push_back(point);}
    PathPosition endSection();

  private:
    PathPosition lastPoint() const {return this->end() - 1;}
  };

}

#endif // PATH_H
