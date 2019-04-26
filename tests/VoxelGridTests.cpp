//
// Created by matt on 25/04/19.
//

#include <gtest/gtest.h>
#include "../include/VoxelGrid.h"

TEST(VoxelGridTests, GetCellTest) {
    Mesh *fakeMesh;
    VoxelGrid grid = VoxelGrid(fakeMesh, 1, 8);

    Box expectedCell = Box(Vec3(5, 5, 5), Vec3(6, 6, 6));
    Box cell = grid.getCell(5, 5, 5);

    EXPECT_EQ(expectedCell.minimum, cell.minimum);
    EXPECT_EQ(expectedCell.maximum, cell.maximum);
}

TEST(VoxelGridTests, VoxeliseTestTeddy) {
    Mesh mesh = Mesh("/home/matt/CLionProjects/mesh-voxeliser/teddy.obj");
    VoxelGrid grid = VoxelGrid(&mesh, 70, 8);

    grid.voxelise();
    //grid.writeToFile();
}

TEST(VoxelGridTests, VoxeliseTestBunny) {
    Mesh mesh = Mesh("/home/matt/CLionProjects/mesh-voxeliser/bunny.obj");
    VoxelGrid grid = VoxelGrid(&mesh, 70, 8);

    grid.voxelise();
    //grid.writeToFile();
}