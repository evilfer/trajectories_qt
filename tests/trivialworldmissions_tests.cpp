


#include <gtest/gtest.h>

#include "helpers/dummyworldloader.h"
#include "helpers/missioncreator.h"

#include "simulator.h"

class TrivialWorldTest : public testing::Test {
public:

    world::SolarSystem* solarsystem;
    simulator::Simulator* simulator;


    virtual void SetUp() {
        solarsystem = DummyWorldLoader::loadTrivialSolarSystem();
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


TEST_F(TrivialWorldTest, NotNull) {
    ASSERT_TRUE(solarsystem);
}

TEST_F(TrivialWorldTest, NotEmpty) {
    ASSERT_EQ(1, solarsystem->bodies().vector().size());
}

TEST_F(TrivialWorldTest, EmptyTrajectory) {
    auto mission = MissionCreator::empty();
    simulator->simulate(mission);

    ASSERT_EQ(0, simulator->trajectory().roots().size());
    ASSERT_EQ(0, simulator->trajectory().sections().size());
    ASSERT_DOUBLE_EQ(MissionCreator::MASS, simulator->world()->ship()->shipmass());
}

TEST_F(TrivialWorldTest, StateTrajectory) {
    auto mission = MissionCreator::fixedPoint();
    simulator->simulate(mission);

    ASSERT_EQ(1, simulator->trajectory().roots().size());
    EXPECT_EQ(1, simulator->trajectory().sections().size());
    ASSERT_EQ("0", simulator->trajectory().roots()[0]);

    const trajectory::PathSection & section = simulator->trajectory().sections().at("0");
    ASSERT_EQ(0, section.length());

    const trajectory::PathPoint & point = *section.from();
    EXPECT_DOUBLE_EQ(0, point.t());
    EXPECT_DOUBLE_EQ(MissionCreator::X0, point.xyz()[0]);
    EXPECT_DOUBLE_EQ(0, point.xyz()[1]);
    EXPECT_DOUBLE_EQ(0, point.xyz()[2]);
    EXPECT_DOUBLE_EQ(0, point.vxyz()[0]);
    EXPECT_DOUBLE_EQ(0, point.vxyz()[1]);
    EXPECT_DOUBLE_EQ(0, point.vxyz()[2]);
}

TEST_F(TrivialWorldTest, WaitTrajectory) {
    auto mission = MissionCreator::wait1Trajectory();
    simulator->simulate(mission);

    ASSERT_EQ(1, simulator->trajectory().roots().size());
    ASSERT_EQ(2, simulator->trajectory().sections().size());
    ASSERT_EQ(1, simulator->trajectory().children("0").size());
    ASSERT_EQ("0.0", simulator->trajectory().children("0")[0]);

    const trajectory::PathSection & section = simulator->trajectory().sections().at("0");
    ASSERT_EQ(0, section.length());

    const trajectory::PathPoint & point = *section.from();
    EXPECT_DOUBLE_EQ(0, point.t());
    EXPECT_DOUBLE_EQ(MissionCreator::X0, point.xyz()[0]);
    EXPECT_DOUBLE_EQ(0, point.xyz()[1]);
    EXPECT_DOUBLE_EQ(0, point.xyz()[2]);
    EXPECT_DOUBLE_EQ(0, point.vxyz()[0]);
    EXPECT_DOUBLE_EQ(0, point.vxyz()[1]);
    EXPECT_DOUBLE_EQ(0, point.vxyz()[2]);
}


