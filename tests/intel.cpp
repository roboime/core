#include "gtest/gtest.h"

#include "intel.h"

class IntelTest : public ::testing::Test {
protected:
  ime::Intel intel;
};

TEST_F(IntelTest, NoOpenSubprocess) {
  ASSERT_FALSE(intel.run());
}

TEST_F(IntelTest, FileOpening) {
  ASSERT_FALSE(intel.start(nullptr, ""));

  // FIXME(naum): "test_roboime_core" should be added by CMake,
  // FIXME(naum): to ensure the name is the same used by CMake
  ASSERT_TRUE(intel.start(nullptr, "test_roboime_core"));
}

// TODO(naum): Mock subprocess
