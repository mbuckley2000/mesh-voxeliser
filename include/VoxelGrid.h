//
// Created by matt on 25/04/19.
//

#ifndef VOXELISE_VOXELGRID_H
#define VOXELISE_VOXELGRID_H


#include "Mesh.h"

class VoxelGrid {
public:
    VoxelGrid(Mesh *mesh, float cellSize);

    Box getCell(int x, int y, int z);

    void voxeliserThread(int threadID, int numThreads, float resolution);
    void voxelise();

    void writeToFile();
private:
    float cellSize;
    Mesh *mesh;

    void set3dBoolArrayToFalse(bool ***array, int xSize, int ySize, int zSize);

    bool ***allocate3dBoolArray(int xSize, int ySize, int zSize);

    void free3dBoolArray(bool ***array, int xSize, int ySize, int zSize);

    bool ***volumeData;
};


#endif //VOXELISE_VOXELGRID_H