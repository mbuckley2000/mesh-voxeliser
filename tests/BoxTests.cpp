#include <gtest/gtest.h>
#include <stdio.h>
#include "../include/Box.h"

TEST(BoxTests, GetVerticesTest)
{
  Vec3 min = Vec3(0, 0, 0);
  Vec3 max = Vec3(1, 1, 1);

  Box b = Box(min, max);

  Eigen::MatrixXf expected(8, 3);
  // matrix of row vectors
  expected << 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1;

  Eigen::MatrixXf mat = b.getVertices();

  EXPECT_EQ(expected.transpose(), mat);
}

// Test constructor
TEST(BoxTests, BoxInitMinMaxConstructor)
{
  Vec3 min = Vec3(-1, 0, 1);
  Vec3 max = Vec3(1, 2, 3);

  Box b = Box(min, max);

  EXPECT_EQ(b.minimum, min);
  EXPECT_EQ(b.maximum, max);
}

// Test constructor
TEST(BoxTests, BoxInitDefaultConstructor)
{
  Vec3 min = Vec3(INFINITY, INFINITY, INFINITY);
  Vec3 max = Vec3(-INFINITY, -INFINITY, -INFINITY);

  Box b = Box();

  EXPECT_EQ(b.minimum, min);
  EXPECT_EQ(b.maximum, max);
}

TEST(BoxTests, GetSize)
{
  Vec3 min = Vec3(-10, -10, -10);
  Vec3 max = Vec3(10, 10, 10);

  Box b = Box(min, max);

  Vec3 expectedSize(20, 20, 20);

  EXPECT_EQ(expectedSize, b.getSize());
}

TEST(BoxTests, Intersects)
{
  Vec3 min = Vec3(-10, -10, -10);
  Vec3 max = Vec3(10, 10, 10);

  Box b = Box(min, max);

  Box b2(Vec3(0, 0, 0), Vec3(1, 1, 1));
  Box b3(Vec3(2, 2, 2), Vec3(3, 3, 3));
  Box b4(Vec3(10, 10, 10), Vec3(33, 33, 33));

  EXPECT_TRUE(b.intersects(&b));
  EXPECT_TRUE(b.intersects(&b2));
  EXPECT_TRUE(b2.intersects(&b));
  EXPECT_TRUE(b4.intersects(&b));
  EXPECT_TRUE(b.intersects(&b4));
  EXPECT_FALSE(b4.intersects(&b2));
}

TEST(BoxTests, LargestDim)
{
  Box b(Vec3(0, 0, 0), Vec3(1, 2, 3));
  EXPECT_EQ(2, b.largestDim());
}

TEST(BoxTests, ExpandBox)
{
  Box b1(Vec3(0, 0, 0), Vec3(1, 1, 1));
  Box b2(Vec3(3, 3, 3), Vec3(5, 5, 5));

  b1.expand(b2);

  EXPECT_EQ(b1.minimum, Vec3(0, 0, 0));
  EXPECT_EQ(b1.maximum, Vec3(5, 5, 5));
}

TEST(BoxTests, ExpandVec)
{
  Box b1(Vec3(0, 0, 0), Vec3(1, 1, 1));

  b1.expand(Vec3(5, 5, 5));

  EXPECT_EQ(b1.minimum, Vec3(0, 0, 0));
  EXPECT_EQ(b1.maximum, Vec3(5, 5, 5));
}