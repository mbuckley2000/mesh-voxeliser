#include <gtest/gtest.h>
#include <sys/stat.h>
#include <iostream>
#include "../include/Mesh.h"
#include "../include/VoxelGrid.h"

bool fileExists(const std::string &name)
{
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char *argv[])
{

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}