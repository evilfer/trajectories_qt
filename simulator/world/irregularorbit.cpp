#include "irregularorbit.h"

namespace world {

IrregularOrbit::IrregularOrbit(int size) : size_(size), points_() {
    this->points_ = new double[3 * size];
}

IrregularOrbit::~IrregularOrbit() {
    delete[] this->points_;
}

}
