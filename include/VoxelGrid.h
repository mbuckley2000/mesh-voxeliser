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

private:
    float cellSize;
    Mesh *mesh;
};


#endif //VOXELISE_VOXELGRID_H
