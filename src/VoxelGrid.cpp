//
// Created by matt on 25/04/19.
//

#include "../include/VoxelGrid.h"

//construct with mesh
//size of bb


//Mesh must start at 0,0,0
VoxelGrid::VoxelGrid(Mesh *mesh, float cellSize) {
    this->mesh = mesh;
    this->cellSize = cellSize;
}

Box VoxelGrid::getCell(int x, int y, int z) {
    //Starting grid from 0, 0, 0

    //Multiply coordinate by cell size to get start of box
    Vec3 minimum = Vec3(x, y, z) * this->cellSize;
    //Box is a cube, same size as cell size
    Vec3 maximum = minimum + Vec3(this->cellSize, this->cellSize, this->cellSize);

    return Box(minimum, maximum);
}