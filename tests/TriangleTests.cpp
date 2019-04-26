#include <gtest/gtest.h>
#include "../include/Triangle.h"

// bool Triangle::intersects(Box *box)

TEST(TriangleTests, TriangleInitVecs)
{
    Vec3 v0 = Vec3(110, 0, 880);
    Vec3 v1 = Vec3(1555, 1, 17);
    Vec3 v2 = Vec3(61, 135, 22);

    Triangle t = Triangle(v0, v1, v2);

    EXPECT_EQ(t.getVertex(0), v0);
    EXPECT_EQ(t.getVertex(1), v1);
    EXPECT_EQ(t.getVertex(2), v2);
}

TEST(TriangleTests, TriangleInitMat)
{
    Mat3 m = Mat3();

    Vec3 v0 = Vec3(110, 0, 880);
    Vec3 v1 = Vec3(1555, 1, 17);
    Vec3 v2 = Vec3(61, 135, 22);

    m << v0, v1, v2;

    Triangle t = Triangle(m);

    EXPECT_EQ(t.getVertex(0), v0);
    EXPECT_EQ(t.getVertex(1), v1);
    EXPECT_EQ(t.getVertex(2), v2);
}

struct intersectState
{
    Triangle triangle;
    Box box;
    bool success;
};

struct TriangleIntersectsBoxTest : testing::Test, testing::WithParamInterface<intersectState>
{
    // Can do initial values here
};

TEST_P(TriangleIntersectsBoxTest, TriangleIntersectsBox)
{
    auto params  = GetParam();
    bool success = params.triangle.intersects(&params.box);

    EXPECT_EQ(success, params.success);
}

INSTANTIATE_TEST_CASE_P

    (Default,
     TriangleIntersectsBoxTest,
     testing::Values(intersectState{Triangle(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(0, 1, 0)), Box(Vec3(0, 0, 0), Vec3(1, 1, 1)), true},
                     intersectState{Triangle(Vec3(0, 0, 0), Vec3(-1, -1, -1), Vec3(0, -1, 0)), Box(Vec3(0, 0, 0), Vec3(1, 1, 1)), true},
                     intersectState{Triangle(Vec3(0.1, 0.1, 0.1), Vec3(0.3, 0.3, 0.3), Vec3(0.1, 0.3, 0.1)), Box(Vec3(0, 0, 0), Vec3(1, 1, 1)), true},
                     intersectState{Triangle(Vec3(100, 100, 100), Vec3(101, 101, 101), Vec3(100, 101, 100)), Box(Vec3(0, 0, 0), Vec3(1, 1, 1)),
                                    false},
                     intersectState{Triangle(Vec3(-1, 0, 0), Vec3(2, 0, 0), Vec3(-1, -1, 0)), Box(Vec3(0, 0, 0), Vec3(1, 1, 1)), true}));