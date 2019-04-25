//
// Created by matt on 25/04/19.
//

#include <gtest/gtest.h>
#include "../include/VoxelGrid.h"

TEST(VoxelGridTests, GetCellTest) {
    Mesh *fakeMesh;
    VoxelGrid grid = VoxelGrid(fakeMesh, 1);

    Box expectedCell = Box(Vec3(5, 5, 5), Vec3(6, 6, 6));
    Box cell = grid.getCell(5, 5, 5);

    EXPECT_EQ(expectedCell.minimum, cell.minimum);
    EXPECT_EQ(expectedCell.maximum, cell.maximum);
}