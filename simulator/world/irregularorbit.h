#ifndef IRREGULARORBIT_H
#define IRREGULARORBIT_H

namespace world {


class IrregularOrbit {
    int size_;
    double *points_;

public:
    IrregularOrbit(int size);
    ~IrregularOrbit();

    inline int size() const {return size_;}
    inline const double * get(int i) const {return & this->points_[3*i];}
    inline double * get(int i) {return & this->points_[3*i];}
};


}

#endif // IRREGULARORBIT_H
