

#include <gtest/gtest.h>

#include "helpers/dummyworldloader.h"

class DummyWorldLoaderTest : public testing::Test {
public:

    world::SolarSystem * solarsystem_;

    virtual void SetUp() {
        solarsystem_ = DummyWorldLoader::loadEarthSolarSystem();
      }

    virtual void TearUp() {
        if (solarsystem_) {
            delete solarsystem_;
        }
    }
};


TEST_F(DummyWorldLoaderTest, NotNull) {
    ASSERT_TRUE(solarsystem_);
}

TEST_F(DummyWorldLoaderTest, HasEarth) {
    ASSERT_EQ(1, solarsystem_->bodies().vector().size());
}

TEST_F(DummyWorldLoaderTest, EarthaAtOrigin) {
    ASSERT_FLOAT_EQ(0, solarsystem_->sun()->pos()[0]);
    ASSERT_FLOAT_EQ(0, solarsystem_->sun()->pos()[1]);
    ASSERT_FLOAT_EQ(0, solarsystem_->sun()->pos()[2]);

    ASSERT_FLOAT_EQ(0, solarsystem_->sun()->vel()[0]);
    ASSERT_FLOAT_EQ(0, solarsystem_->sun()->vel()[1]);
    ASSERT_FLOAT_EQ(0, solarsystem_->sun()->vel()[2]);
}



