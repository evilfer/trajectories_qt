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


#ifndef EPHEMERIDES_SPICEPOSITION_H
#define EPHEMERIDES_SPICEPOSITION_H


#include <vector>
#include <map>
#include <string>

#include <SpiceUsr.h>
#include "bodyconstants.h"

namespace ephemerides {


  class SpicePosition {

    static double m_lt;
    static BodyConstantsList m_bodies;
    static EphemeridesIntervalMap m_intervals;
    static EphemeridesInterval m_interval;

  private:

    static void kernels(std::vector<std::string> &list);
    static void getbodies(const std::string & kernel);
    static void getinterval(const std::vector<std::string> & kernels, BodyId body, EphemeridesInterval & interval);

  public:
    static void init();
    static inline void getpos(int body, double et, double *xyz) {spkgps_c (body, et, "ECLIPJ2000", 0, xyz, &m_lt);}
    static inline void getposvel(int body, double et, double *pv) {spkgeo_c (body, et, "ECLIPJ2000", 0, pv, &m_lt);}

    static inline const BodyConstantsList & bodies() {return m_bodies;}

    static inline const EphemeridesInterval & interval() {return m_interval;}
  };

}


#endif
