#include "pathpoint.h"

namespace trajectory {

  PathPoint::PathPoint()
  {
    this->t_ = 0;
    std::fill(this->xyz_, this->xyz_+3, 0);
    std::fill(this->vxyz_, this->xyz_+3, 0);
  }

  PathPoint::PathPoint(const PathPoint &point)
  {
    this->t_ = point.t_;
    std::copy(point.xyz(), point.xyz() + 3, this->xyz_);
    std::copy(point.vxyz(), point.vxyz() + 3, this->vxyz_);
  }

}
