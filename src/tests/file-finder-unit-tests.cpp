#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Container.h"

using namespace ff;

// This is a Google Test unit test that I will not bother to do,
// but you get the idea I am sure.

class FFUnitTest : public testing::Test {
    //  Fixture stuff
};

TEST_F(FFUnitTest, Add) {
    Container c;
    string str("/tmp/file");
    EXPECT_NO_THROW(c.Add(str));  // That sort of thing
}

// A bunch more tests, then integrate gcov into CMake... Python smoke tests... oh the humanity!
