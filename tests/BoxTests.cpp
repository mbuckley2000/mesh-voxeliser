#include <gtest/gtest.h>
#include <stdio.h>
#include "../include/Box.h"

TEST(BoxTests, GetVerticesTest)
{
    Vec3 min = Vec3(0, 0, 0);
    Vec3 max = Vec3(1, 1, 1);

    Box b = Box(min, max);

    Eigen::MatrixXf expected(8, 3);
    expected << 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1;

    Eigen::MatrixXf mat = b.getVertices();

    EXPECT_EQ(expected.transpose(), mat);
}

TEST(BoxTests, BoxInit)
{
    Vec3 min = Vec3(-1, 0, 1);
    Vec3 max = Vec3(1, 2, 3);

    Box b = Box(min, max);

    EXPECT_EQ(b.minimum, min);
    EXPECT_EQ(b.maximum, max);
}

struct containsState
{
    Vec3 vec;
    Box box;
    bool success;
};

struct BoxContainsVectorTest : testing::Test, testing::WithParamInterface<containsState>
{
    // Can do initial values here
};

TEST_P(BoxContainsVectorTest, BoxContainsVector)
{
    auto params  = GetParam();
    bool success = params.box.contains(params.vec);

    EXPECT_EQ(success, params.success);
}

INSTANTIATE_TEST_CASE_P(
    Default,
    BoxContainsVectorTest,
    testing::Values(containsState{Vec3(1, 1, 1), Box(Vec3(0, 0, 0), Vec3(5, 5, 5)), true},
                    containsState{Vec3(1, 1, 1), Box(Vec3(0, 0, 0), Vec3(0, 0, 0)), false},
                    containsState{Vec3(1, 1, 1), Box(Vec3(2, 2, 2), Vec3(0, 0, 0)), false},
                    containsState{Vec3(0, 0, 0), Box(Vec3(0, 0, 0), Vec3(5, 5, 5)), true},
                    containsState{Vec3(5, 5, 5), Box(Vec3(0, 0, 0), Vec3(5, 5, 5)), true},
                    containsState{Vec3(0, 0, 0), Box(Vec3(0, 0, 0), Vec3(0, 0, 0)), true},
                    containsState{Vec3(1000, 0, 0), Box(Vec3(0, 0, 0), Vec3(1, 1, 1)), false}));