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


#ifndef TMATH_JULIANDAY_H
#define TMATH_JULIANDAY_H

#include <ctime>
#include <string>


namespace tmath {


class JulianDay {

    double m_jd;
    struct tm m_tm;
    double m_j2000;

    void calculateJdFromGd();
    void calculateGdFromJd();
    void calculateJ2000();

public:


    JulianDay();
    ~JulianDay();

    void setJ2000(double j2000);
    bool setGd(const std::string &date);
    void setJd(double jd);


    double getJd() {return m_jd;}
    double getJ2000() {return m_j2000;}
    const std::string getGd();

    int getYear() const {return m_tm.tm_year + 1900;}
};




}

#endif // JULIANDAY_H
