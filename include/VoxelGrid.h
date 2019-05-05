#ifndef VOXELISE_VOXELGRID_H
#define VOXELISE_VOXELGRID_H

#include "Mesh.h"

class VoxelGrid
{
public:
  VoxelGrid(Mesh *mesh, int resolution, int numThreads);
  ~VoxelGrid();

  Box getCell(int x, int y, int z);

  void voxeliserThread(int threadID);
  void voxelise();

  void writeToFile(char *filename);

private:
  int resolution;
  int numThreads;
  bool allocated = false;
  float cellSize;
  Mesh *mesh;

  static void set3dBoolArrayToFalse(bool ***array, int xSize, int ySize, int zSize);

  static bool ***allocate3dBoolArray(int xSize, int ySize, int zSize);

  static void free3dBoolArray(bool ***array, int xSize, int ySize, int zSize);

  bool ***volumeData;
};

#endif  // VOXELISE_VOXELGRID_H
