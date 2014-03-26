#ifndef DUMMYWORLDLOADER_H
#define DUMMYWORLDLOADER_H

#include "world/solarsystem.h"

class DummyWorldLoader {
public:

    static world::SolarSystem *loadEarthSolarSystem();
    static world::SolarSystem *loadEmptySolarSystem();
    static world::SolarSystem *loadTrivialSolarSystem();
};

#endif // DUMMYWORLDLOADER_H
