#include "dummyworldloader.h"
#include "ephemerides/spiceposition.h"

world::SolarSystem* DummyWorldLoader::loadEarthSolarSystem() {
    world::SolarSystem* solarSystem = new world::SolarSystem();
    ephemerides::SpicePosition::init();
    const ephemerides::BodyConstantsList& bodies = ephemerides::SpicePosition::bodies();
    const ephemerides::BodyConstants* earth = bodies["earth"];
    ephemerides::BodyConstants fixedEarth(0, earth->name(), earth->radius(), earth->gm(), 0);
    solarSystem->setSun(&fixedEarth);
    solarSystem->update(0);

    return solarSystem;
}

world::SolarSystem* DummyWorldLoader::loadEmptySolarSystem() {
    world::SolarSystem* solarSystem = new world::SolarSystem();
    solarSystem->update(0);
    return solarSystem;
}

world::SolarSystem* DummyWorldLoader::loadTrivialSolarSystem() {
    world::SolarSystem* solarSystem = new world::SolarSystem();
    ephemerides::SpicePosition::init();
    ephemerides::BodyConstants fixedSun(0, "", 1, 0, 0);
    solarSystem->setSun(&fixedSun);
    solarSystem->update(0);

    return solarSystem;
}
