//
// Created by matt on 25/04/19.
//

#include "../include/VoxelGrid.h"
#include <iostream>
#include <fstream>

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

void VoxelGrid::voxelise() {
    int resolution = 1 / this->cellSize;

    this->volumeData = this->allocate3dBoolArray(resolution, resolution, resolution);
    this->set3dBoolArrayToFalse(this->volumeData, resolution, resolution, resolution);

    std::stringstream filename;
    filename << "voxel_" << resolution << "x" << resolution << "x" << resolution << "_uint8.raw";
    std::ofstream myfile(filename.str(), std::ios::out | std::ios::binary);
    //std::ofstream myfile("out.vox");
    //myfile << resolution << "," << resolution << "," << resolution << ";";


    for (int x = 0; x < resolution; x++) {
        for (int y = 0; y < resolution; y++) {
            for (int z = 0; z < resolution; z++) {
                Box box = this->getCell(x, y, z);
                if (this->mesh->intersects(&box)) {
                    //Set to 1
                    this->volumeData[z][y][x] = true;
                    //myfile << x << "," << y << "," << z << ";";
                    myfile << (uint8_t) 255; //raw format
                } else {
                    myfile << (uint8_t) 0; //raw format
                }
            }
        }
    }

    myfile.close();
}


void VoxelGrid::writeToFile() {
    std::ofstream myfile;
    myfile.open("output.txt");
    myfile << "Writing this to a file.\n";
    myfile.close();
}

void VoxelGrid::set3dBoolArrayToFalse(bool ***array, int xSize, int ySize, int zSize) {
    for (int z = 0; z < zSize; z++) {
        for (int y = 0; y < ySize; y++) {
            for (int x = 0; x < xSize; x++) {
                array[z][y][x] = false;
            }
        }
    }
}

bool ***VoxelGrid::allocate3dBoolArray(int xSize, int ySize, int zSize) {
    bool ***data = (bool ***) malloc(sizeof(bool **) * zSize);
    for (int z = 0; z < zSize; z++) {
        data[z] = (bool **) malloc(sizeof(bool *) * ySize);
        for (int y = 0; y < ySize; y++) {
            data[z][y] = (bool *) malloc(sizeof(bool) * xSize);
        }
    }

    return data;
}


void VoxelGrid::free3dBoolArray(bool ***array, int xSize, int ySize, int zSize) {

    for (int z = 0; z < zSize; z++) {
        for (int y = 0; y < ySize; y++) {
            free(array[z][y]);
        }
        free(array[z]);
    }

    free(array);
}