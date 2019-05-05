#include <gtest/gtest.h>
#include "../include/VoxelGrid.h"

TEST(VoxelGridTests, GetCellTest)
{
  Mesh *fakeMesh;
  VoxelGrid grid = VoxelGrid(fakeMesh, 10, 8);

  Box expectedCell = Box(Vec3(0.5, 0.5, 0.5), Vec3(0.6, 0.6, 0.6));
  Box cell         = grid.getCell(5, 5, 5);

  EXPECT_EQ(expectedCell.minimum, cell.minimum);
  EXPECT_EQ(expectedCell.maximum, cell.maximum);
}

TEST(VoxelGridTests, VoxeliseTestTeddy)
{
  Mesh mesh      = Mesh("/home/matt/CLionProjects/voxelise/teddy.obj");
  VoxelGrid grid = VoxelGrid(&mesh, 100, 8);

  grid.voxelise();
  grid.writeToFile("/home/matt/dev/diss/vixel-renderer/testout.raw");
}