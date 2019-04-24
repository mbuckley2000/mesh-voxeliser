//
// Some example gtest tests for Eigen library
// Created by matt on 24/04/19.
//

#include <gtest/gtest.h>
#include <Eigen/Dense>

TEST(EigenTests, VectorInitToZero) {
    Eigen::Vector2i v = Eigen::Vector2i(0,0);

    EXPECT_FLOAT_EQ(0, v(0));
    EXPECT_FLOAT_EQ(0, v(1));
}

TEST(EigenTests, VectorSum) {
    Eigen::Vector2i v = Eigen::Vector2i(1,2);
    Eigen::Vector2i v2 = Eigen::Vector2i(3, 4);

    Eigen::Vector2i v3 = v + v2;

    EXPECT_FLOAT_EQ(4, v3(0));
    EXPECT_FLOAT_EQ(6, v3(1));
}