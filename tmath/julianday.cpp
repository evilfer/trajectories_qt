#include "julianday.h"
#include "consts.h"

#ifdef _TRAJECTORIES_USE_OWN_WIN_STRPTIME
#include "win/strptime.h"
#endif

#include <cmath>
#include <cstring>


namespace tmath {

JulianDay::JulianDay() {
}


JulianDay::~JulianDay() {
}

void JulianDay::calculateJdFromGd() {
    int a = (14-(m_tm.tm_mon + 1)) / 12;
    int y = (1900 + m_tm.tm_year) - a;
    int m = (m_tm.tm_mon + 1) + 12*a -3;

    int jdn = m_tm.tm_mday + (153*m + 2) / 5 + 365 * y + y/4 - y/100 + y/400 - 678882;

    m_jd = jdn + m_tm.tm_hour / 24. + m_tm.tm_min / 1440. + m_tm.tm_sec / 86400.;
}

void JulianDay::calculateGdFromJd() {
    memset(&m_tm, 0 , sizeof(m_tm));
    int jdn = (int) floor(m_jd) + 2400001;

    int j = jdn + 32044;
    int g = j / 146097;
    int dg =  j % 146097;

    int c = (dg / 36524 + 1) * 3 / 4;
    int dc = dg - c * 36524;

    int b = dc / 1461;
    int db = dc % 1461;

    int a = (db / 365 + 1) * 3 / 4;
    int da = db - a * 365;

    int y = g * 400 + c * 100 + b * 4 + a;
    int m = (da * 5 + 308) / 153 - 2;
    int d = da - (m + 4) * 153 / 5 + 122;


    m_tm.tm_year = (y - 4800 + (m + 2) / 12) - 1900;
    m_tm.tm_mon = ((m + 2) % 12 + 1) - 1;
    m_tm.tm_mday = d + 1;

    double t = m_jd - floor(m_jd);

    m_tm.tm_hour = (int) floor(t * 24);
    m_tm.tm_min = (int) floor(t*1440 - 60*m_tm.tm_hour);
    m_tm.tm_sec = (int) (t*86400. - 3600. * m_tm.tm_hour - 60.*m_tm.tm_min);
}




void JulianDay::calculateJ2000() {
    m_j2000 = m_jd * 86400.0 - J2000MJDsec;
}



void JulianDay::setJd(double jd) {
    m_jd = jd;
    calculateGdFromJd();
    calculateJ2000();
}



bool JulianDay::setGd(const std::string &date) {
    char * nextchar = strptime(date.c_str(), "%Y-%m-%dT%H:%M:%S", &m_tm);

    calculateJdFromGd();
    calculateJ2000();

    return nextchar != 0;
}

void JulianDay::setJ2000(double j2000) {
    m_j2000 = j2000;
    m_jd = (j2000 + J2000MJDsec) / 86400.0;
    calculateGdFromJd();
}

const std::string JulianDay::getGd() {
    static char str[100];
    strftime(str, 99, "%Y-%m-%dT%H:%M:%S", &m_tm);
    return std::string(str);
}

}
