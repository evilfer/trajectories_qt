#include "vectormath.h"

namespace tmath {

  double distance(const double * v1, const double * v2) {
    double xyz[3];
    substract(v1, v2, xyz);
    return mod(xyz);
  }

  void rotate(const double *v, double angle, const double * axis, double *result) {
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    double i_cos_a = 1 - cos_a;
    double x_i_cos_a = axis[0] * i_cos_a;
    double y_i_cos_a = axis[1] * i_cos_a;
    double z_i_cos_a = axis[2] * i_cos_a;
    double xy_i_cos_a = axis[0] * y_i_cos_a;
    double xz_i_cos_a = axis[0] * z_i_cos_a;
    double yz_i_cos_a = axis[1] * z_i_cos_a;
    double x_sin_a = axis[0] * sin_a;
    double y_sin_a = axis[1] * sin_a;
    double z_sin_a = axis[2] * sin_a;


    /* a b c
       d e f
       g h i */

    double a = cos_a + axis[0] * x_i_cos_a;
    double b = xy_i_cos_a - x_sin_a;
    double c = xz_i_cos_a + y_sin_a;
    double d = xy_i_cos_a + z_sin_a;
    double e = cos_a + axis[1] * y_i_cos_a;
    double f = yz_i_cos_a - x_sin_a;
    double g = xz_i_cos_a - y_sin_a;
    double h = yz_i_cos_a + x_sin_a;
    double i = cos_a + axis[2] * z_i_cos_a;

    double x = a * v[0] + b * v[1] + c * v[2];
    double y = d * v[0] + e * v[1] + f * v[2];
    double z = g * v[0] + h * v[1] + i * v[2];

    set(x, y, z, result);
  }

  void interpolate(const double *v1, const double *v2, double k, double * result) {
    substract(v2, v1, result);
    scale(result, k);
    add(result, v1);
  }
}
