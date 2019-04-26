#include <gtest/gtest.h>
#include "../include/Triangle.h"
#include "../include/TriangleKDNode.h"

TEST(TriangleKDNodeTests, EmptyLeafConstructor)
{
    TriangleKDNode node = TriangleKDNode();

    EXPECT_TRUE(node.triangles.empty());
    EXPECT_EQ(node.left, nullptr);
    EXPECT_EQ(node.right, nullptr);
}

TEST(TriangleKDNodeTests, TriangleConstructor)
{
    std::vector<Triangle *> vec = std::vector<Triangle *>();

    for (int i = 0; i < 100; i++)
    {
        Triangle *t = new Triangle(Vec3(i * 100, i * 100, i * 100), Vec3(i / 100, i / 100, i / 100),
                                   Vec3(2 * i, 2 * i, 2 * i));
        vec.push_back(t);
    }

    TriangleKDNode node = TriangleKDNode(vec);

    EXPECT_FALSE(node.triangles.empty());
    EXPECT_NE(node.left, nullptr);
    EXPECT_NE(node.right, nullptr);
}