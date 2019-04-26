//
// Created by matt on 24/04/19.
//

#include <gtest/gtest.h>
#include "../include/Mesh.h"

TEST(MeshTests, LoadMesh)
{
    Mesh mesh = Mesh("/home/matt/CLionProjects/mesh-voxeliser/teddy.obj");

    EXPECT_FALSE(mesh.triangles.empty());
}

TEST(MeshTests, MeshNormalisation)
{
    Mesh mesh = Mesh("/home/matt/CLionProjects/mesh-voxeliser/teddy.obj");

    EXPECT_FLOAT_EQ(mesh.boundingBox.getSize()(mesh.boundingBox.largestDim()), 1);
}

TEST(MeshTests, MoveMeshToOrigin)
{
    Mesh mesh   = Mesh("/home/matt/CLionProjects/mesh-voxeliser/teddy.obj");
    Vec3 origin = Vec3(0, 0, 0);
    EXPECT_EQ(mesh.boundingBox.minimum, origin);
}

TEST(MeshTests, IntersectFalse)
{
    Mesh mesh = Mesh("/home/matt/CLionProjects/mesh-voxeliser/teddy.obj");
    Box box   = Box(Vec3(100, 100, 100), Vec3(101, 101, 101));

    EXPECT_FALSE(mesh.intersects(&box));
}

TEST(MeshTests, IntersectTrue)
{
    Mesh mesh = Mesh("/home/matt/CLionProjects/mesh-voxeliser/teddy.obj");
    Box box   = Box(Vec3(-100, -100, -100), Vec3(101, 101, 101));

    EXPECT_TRUE(mesh.intersects(&box));
}