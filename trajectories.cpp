#include "trajectories.h"

#include "simulator/ephemerides/spiceposition.h"
#include "model/store.h"


Trajectories::Trajectories(): store_(NULL) {
    this->init();
}

Trajectories::~Trajectories() {
    if (this->store_) {
        delete this->store_;
    }
}

void Trajectories::processCall(int op, QVariantMap & data) {

}

void Trajectories::init() {

    ephemerides::SpicePosition::init();

    model::TObjectModelMap model = {
        {"Simulation", {
             true,
             {
                 {"metadata", TOBJECT_PARAM_OWNEDLINK}
             }
         }
        },
        {"SimulationMetadataa", {
             true,
             {
                 {"title", TOBJECT_PARAM_STRING},
                 {"description", TOBJECT_PARAM_STRING},
                 {"simulation", TOBJECT_PARAM_LINK}
             }
         }
        }
    };

    this->store_ = new model::Store(model);
}



