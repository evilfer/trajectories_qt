#include "trajectories.h"

#include "simulator/ephemerides/spiceposition.h"
#include <iostream>

Trajectories::Trajectories() : EmberCppJsListener() {
    this->init();
}

Trajectories::~Trajectories() {
}

void Trajectories::prepareCreateResponse(const std::string & , QVariantMap & ) {

}

void Trajectories::prepareUpdateResponse(const std::string & type, QVariantMap & record) {
    if (type == "solar_system_state") {
        record["bodies"] = QVariantMap();
    }
}



