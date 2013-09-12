#include "trajectories.h"

#include "simulator/ephemerides/spiceposition.h"

void Trajectories::init() {

    ephemerides::SpicePosition::init();

    model::TObjectModelMap model = {
        {"simulation", {
             /*solid*/ true,
             /*plural*/ "simulations",
             /*params*/ {},
             /*links*/ {
                 {"metadata", {true, false, "simulation_metadata", "metadata", "metadata_key", false}},
                 {"config", {true, false, "simulation_configuration", "config", "config_key", false}},
                 {"ship", {true, false, "ship", "ship", "ship_key", false}},
                 {"mission", {true, false, "mission", "mission", "mission_key", false}}
             },
             /*arrays*/ {}
         }},
        {"simulation_metadata", {
             /*solid*/ true,
             /*plural*/ "simulation_metadatas",
             /*params*/ {
                 {"title", TOBJECT_PARAM_STRING},
                 {"description", TOBJECT_PARAM_STRING},
                 {"author", TOBJECT_PARAM_STRING},
                 {"modified", TOBJECT_PARAM_STRING}
             },
             /*links*/ {
                 {"simulation", {false, false, "simulation", "simulation", "simulation_type", false}}
             },
             /*arrays*/ {}
         }},
        {"simulation_configuration", {
             /*solid*/ true,
             /*plural*/ "simulation_configurations",
             /*params*/ {
                 {"ephemerides", TOBJECT_PARAM_STRING}
             },
             /*links*/ {
                 {"simulation", {false, false, "simulation", "simulation", "simulation_type", false}}
             },
             /*arrays*/ {}
         }},
        {"ship", {
             /*solid*/ true,
             /*plural*/ "ships",
             /*params*/ {
                 {"name", TOBJECT_PARAM_STRING},
                 {"mass", TOBJECT_PARAM_DOUBLE},
                 {"thrust", TOBJECT_PARAM_DOUBLE},
                 {"isp", TOBJECT_PARAM_DOUBLE},
                 {"fuelmass", TOBJECT_PARAM_DOUBLE},
             },
             /*links*/ {
                 {"simulation", {false, false, "simulation", "simulation", "simulation_type", false}}
             },
             /*arrays*/ {}
         }},
        {"mission", {
             /*solid*/ true,
             /*plural*/ "missions",
             /*params*/ {
                 {"duration", TOBJECT_PARAM_DOUBLE},
             },
             /*links*/ {
                 {"simulation", {false, false, "simulation", "simulation", "simulation_type", false}},
                 {"start", {true, false, "mission_start", "start", "start_type", false}}
             },
             /*arrays*/ {
             }
         }},
        {"mission_start", {
             /*solid*/ true,
             /*plural*/ "mission_starts",
             /*params*/ {
                 {"date", TOBJECT_PARAM_DOUBLE},
                 {"planet", TOBJECT_PARAM_STRING},
                 {"radius", TOBJECT_PARAM_DOUBLE},
                 {"inclination", TOBJECT_PARAM_DOUBLE},
                 {"longitude", TOBJECT_PARAM_DOUBLE},
                 {"latitude", TOBJECT_PARAM_DOUBLE},
             },
             /*links*/ {
                 {"mission", {false, false, "mission", "mission", "mission_type", false}},
             },
             /*arrays*/ {}
         }},
        {"solar_system_state", {
             /*solid*/ false,
             /*plural*/ "solar_system_states",
             /*params*/ {
                 {"date", TOBJECT_PARAM_DOUBLE},
             },
             /*links*/ {},
             /*arrays*/ {}
         }},
        {"simulator_data", {
             /*solid*/ false,
             /*plural*/ "s",
             /*params*/ {
                 {"date", TOBJECT_PARAM_DOUBLE},
             },
             /*links*/ {
                 {"simulation", {false, false, "simulation", "simulation", "simulation_type", false}},
                 {"viewdate", {false, false, "solar_system_state", "viewdate", "mission_type", true}},
             },
             /*arrays*/ {}
         }},

    };

    this->setModel(model);
}





