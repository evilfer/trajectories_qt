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

#include "spiceposition.h"

#include <cmath>
#include <cctype>
#include <iostream>

namespace ephemerides {

    double                  SpicePosition::m_lt(0);
    BodyConstantsList       SpicePosition::m_bodies;
    EphemeridesIntervalMap  SpicePosition::m_intervals;
    EphemeridesInterval     SpicePosition::m_interval;




    void SpicePosition::kernels(std::vector<std::string> &list) {
        SpiceChar       file  [128];
        SpiceChar       filtyp[32];
        SpiceChar       source[128];

        SpiceInt        handle;
        SpiceBoolean    found;

        SpiceInt count;
        ktotal_c ("spk", &count);

        for (SpiceInt i = 0; i < count; i++) {
            kdata_c(i, "spk",
                    sizeof(file), sizeof(filtyp), sizeof(source),
                    file, filtyp, source, &handle, &found);
            list.push_back(file);
        }
    }

    void SpicePosition::getbodies(const std::string &kernel) {
        SPICEINT_CELL (ids, 1000);

        spkobj_c(kernel.c_str(), &ids);

        for (SpiceInt i = 0; i < card_c(&ids); i++) {
            SpiceInt obj = SPICE_CELL_ELEM_I(&ids, i);
            int key = obj;
            if (m_bodies[key] == 0) {

                double values[3], radius, gm;
                char name[200];
                SpiceInt dim;
                SpiceBoolean found;

                bodc2n_c(obj, sizeof(name), name, &found);
                if (found) {
                    for (int i = 1; name[i] != 0; i++) {
                        name[i] = tolower(name[i]);
                    }

                    radius = gm = 0;
                    bodvcd_c(obj, "RADII", 3, &dim, values);
                    if (dim == 3) {
                        radius = (values[0] + values[1] + values[2]) / 3.;

                        bodvcd_c(obj, "GM", 1, &dim, values);
                        if (dim > 0) {
                            gm = values[0];

                            BodyConstants bc(obj, name, radius, gm, 40);
                            m_bodies.addBody(new BodyConstants(obj, name, radius, gm, 40));
                        }
                    }
                }
            }
        }

    }

    void SpicePosition::getinterval(const std::vector<std::string> &kernels, BodyId body, EphemeridesInterval &interval) {
        SPICEDOUBLE_CELL        ( cover, 2000);

        bool first = true;

        for (std::vector<std::string>::const_iterator i = kernels.begin(); i != kernels.end(); i++) {
            scard_c(0, &cover);
            spkcov_c(i->c_str(), body, &cover);
            SpiceInt niv = wncard_c (&cover);

            for (SpiceInt j = 0; j < niv; j++) {
                SpiceDouble a, b;
                wnfetd_c(&cover, j, &a, &b);

                if (first) {
                    first = false;
                    interval.a = a;
                    interval.b = b;
                } else {
                    interval.a = std::min(interval.a, a);
                    interval.b = std::max(interval.b, b);
                }
            }
        }

        char timea[1000], timeb[1000];

        timout_c (interval.a, "YYYY ::TDB", sizeof(timea), timea);
        timout_c (interval.b, "YYYY ::TDB", sizeof(timeb), timeb);

        std::cout << body << " " << m_bodies[body]->name() << " ";
        std::cout << "[" << timea << " - " << timeb << "]" << std::endl;
    }

    void SpicePosition::init() {
        erract_c("SET", 0, (char*)"IGNORE");

        const char * k = "../cfg/kernels.furnsh";
        furnsh_c(k);

        std::vector<std::string> ks;
        kernels(ks);

        for (std::vector<std::string>::iterator i = ks.begin(); i != ks.end(); i++) {
            std::cout << *i << std::endl;
            getbodies(*i);
        }



        for (BodyConstantsConstIterator it = m_bodies.begin(); it != m_bodies.end(); it++) {
            EphemeridesInterval & interval = m_intervals[(*it)->id()];
            getinterval(ks, (*it)->id(), interval);

            if (it == m_bodies.begin()) {
                m_interval.a = interval.a;
                m_interval.b = interval.b;
            } else {
                m_interval.a = std::max(m_interval.a, interval.a);
                m_interval.b = std::min(m_interval.b, interval.b);
            }
        }

        m_interval.a += 100;
        m_interval.b -= 100;

        char timea[1000], timeb[1000];

        timout_c (m_interval.a, "YYYY ::TDB", sizeof(timea), timea);
        timout_c (m_interval.b, "YYYY ::TDB", sizeof(timeb), timeb);

        std::cout << "global: [" << m_interval.a << " - " << m_interval.b << "]" << std::endl;
        std::cout << "global: [" << timea << " - " << timeb << "]" << std::endl;

        std::cout << m_bodies.size() << std::endl;

        erract_c("SET", 0, (char*)"DEFAULT");
    }


}
