#include "lib.h"

#include "gtest/gtest.h"
namespace {

TEST(test_valid_version, test_gt) {
  EXPECT_GT(version(), 0);
}

}  // namespace
