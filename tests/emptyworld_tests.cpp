


#include <gtest/gtest.h>

#include "helpers/dummyworldloader.h"
#include "helpers/missioncreator.h"

#include "simulator.h"

class EmptyWorldTest : public testing::Test {
public:

    world::SolarSystem* solarsystem;
    simulator::Simulator* simulator;


    virtual void SetUp() {
        solarsystem = DummyWorldLoader::loadEmptySolarSystem();
        simulator = new simulator::Simulator(solarsystem);
    }

    virtual void TearUp() {
        if (solarsystem) {
            delete solarsystem;
        }

        if (simulator) {
            delete simulator;
        }
    }
};


TEST_F(EmptyWorldTest, NotNull) {
    ASSERT_TRUE(solarsystem);
}

TEST_F(EmptyWorldTest, IsEmpty) {
    ASSERT_EQ(0, solarsystem->bodies().vector().size());
}



