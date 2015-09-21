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

  // TODO(naum): Change magic string "subprocess-repeater" using CMake, to
  // TODO(naum): ensure the string is correct
  ASSERT_TRUE(intel.start(nullptr, "subprocess-repeater"));
}

// TODO(naum): Mock subprocess
