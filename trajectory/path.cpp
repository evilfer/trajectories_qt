#include "path.h"

namespace trajectory {


  Path::Path()
  {
  }

  PathPosition Path::startSection(const PathPoint &startPoint)
  {
    this->save(startPoint);
    return this->lastPoint();
  }


  PathPosition Path::endSection() {
    return this->lastPoint();
  }




}

