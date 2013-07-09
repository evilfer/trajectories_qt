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


#ifndef TVECTOR_VECTORMATH_H
#define TVECTOR_VECTORMATH_H


#include <cmath>

namespace tvector {
    extern const double *X;
    extern const double *Y;
    extern const double *Z;

    inline void add(double *v1, const double *v2) {
        v1[0] += v2[0];
        v1[1] += v2[1];
        v1[2] += v2[2];
    }

    inline void add(const double *v1, const double *v2, double *result) {
        result[0] = v1[0] + v2[0];
        result[1] = v1[1] + v2[1];
        result[2] = v1[2] + v2[2];
    }

    inline void addScaled(double *v1, const double * v2, double k) {
        v1[0] += v2[0] * k;
        v1[1] += v2[1] * k;
        v1[2] += v2[2] * k;
    }

    inline void substract(double *v1, const double * v2) {
        v1[0] -= v2[0];
        v1[1] -= v2[1];
        v1[2] -= v2[2];
    }

    inline void substract(const double* v1, const double* v2, double *result) {
        result[0] = v1[0] - v2[0];
        result[1] = v1[1] - v2[1];
        result[2] = v1[2] - v2[2];
    }

    inline void reset(double *v) {
        v[0] = v[1] = v[2] = .0;
    }


    inline double mod2(const double *v) {
        return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }
    inline double mod(const double *v) {
        return sqrt(mod2(v));
    }

    inline void cross(const double * a, const double* b, double *result) {
        result[0] = a[1] * b[2] - a[2] * b[1];
        result[1] = a[2] * b[0] - a[0] * b[2];
        result[2] = a[0] * b[1] - a[1] * b[0];
    }
    inline double dot(const double* a, const double *b) {
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
    }

    inline void set(double x, double y, double z, double *result) {
        result[0] = x;
        result[1] = y;
        result[2] = z;
    }

    inline void set(const double *v, double *result) {
        result[0] = v[0];
        result[1] = v[1];
        result[2] = v[2];
    }
    inline void setScaled(const double *v, double k, double *result) {
        result[0] = v[0] * k;
        result[1] = v[1] * k;
        result[2] = v[2] * k;
    }

    inline void scale(double *v, double k) {
        v[0] *= k;
        v[1] *= k;
        v[2] *= k;
    }

    inline double unit(double * v) {
        double m = mod(v);
        if (m > .0) {
            scale(v, 1./m);
        }
        return m;
    }

    inline double unit(const double *v, double * result) {
        double m = mod(v);
        if (m > .0) {
            setScaled(v, 1./m, result);
        } else {
            reset(result);
        }
        return m;
    }

    inline void getInRefFrame(const double *v, const double * x, const double * y, const double * z, double * result) {
        result[0] = dot(v, x);
        result[1] = dot(v, y);
        result[2] = dot(v, z);
    }

    double distance(const double * v1, const double * v2);

    void rotate(const double *v, double angle, const double * axis, double *result);
    void interpolate(const double *v1, const double *v2, double k, double * result);

}




#endif // VECTORMATH_H
