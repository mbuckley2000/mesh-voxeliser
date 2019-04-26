#include "../include/VoxelGrid.h"
#include <fstream>
#include <iostream>
#include <thread>

VoxelGrid::VoxelGrid(Mesh *mesh, int resolution, int numThreads)
{
    assert(resolution > 0);
    assert(numThreads > 0);

    this->mesh       = mesh;
    this->resolution = resolution;
    this->cellSize   = 1.0 / resolution;
    this->numThreads = numThreads;
}

VoxelGrid::~VoxelGrid()
{
    if (allocated)
    {
        this->free3dBoolArray(this->volumeData, this->resolution, this->resolution, this->resolution);
    }
}

Box VoxelGrid::getCell(int x, int y, int z)
{
    assert(x >= 0 && y >= 0 && z >= 0);
    assert(x < this->resolution && y < this->resolution && z < this->resolution);

    // Starting grid from 0, 0, 0
    // Multiply coordinate by cell size to get start of box
    Vec3 minimum = Vec3(x, y, z) * this->cellSize;
    // Box is a cube, same size as cell size
    Vec3 maximum = minimum + Vec3(this->cellSize, this->cellSize, this->cellSize);

    return Box(minimum, maximum);
}

void VoxelGrid::voxeliserThread(int threadID)
{
    assert(threadID >= 0);
    assert(threadID < numThreads);

    for (int x = threadID; x < resolution; x += numThreads)
    {
        for (int y = 0; y < resolution; y++)
        {
            for (int z = 0; z < resolution; z++)
            {
                Box box = this->getCell(x, y, z);
                if (this->mesh->intersects(&box))
                {
                    // Set to true
                    this->volumeData[z][y][x] = true;
                }
            }
        }
    }
}

void VoxelGrid::voxelise()
{
    if (allocated)
    {
        free3dBoolArray(volumeData, resolution, resolution, resolution);
    }

    this->volumeData = this->allocate3dBoolArray(resolution, resolution, resolution);
    allocated        = true;
    this->set3dBoolArrayToFalse(this->volumeData, resolution, resolution, resolution);

    // Split workload between threads
    // Each thread gets it's ID and the number of threads
    // It starts at c=ID, then increments by num_threads
    // Interlaced pattern
    // Spreads work
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++)
    {
        threads.push_back(std::thread(&VoxelGrid::voxeliserThread, this, i));
    }

    // Wait for threads to finish
    for (int i = 0; i < numThreads; i++)
    {
        threads[i].join();
    }
}

void VoxelGrid::writeToFile(char *filename)
{
    std::ofstream myfile(filename, std::ios::out | std::ios::binary);

    for (int x = 0; x < resolution; x++)
    {
        for (int y = 0; y < resolution; y++)
        {
            for (int z = 0; z < resolution; z++)
            {
                if (this->volumeData[x][y][z])
                {
                    myfile << (uint8_t)255;
                }
                else
                {
                    myfile << (uint8_t)0;
                }
            }
        }
    }

    myfile.close();
}

void VoxelGrid::set3dBoolArrayToFalse(bool ***array, int xSize, int ySize, int zSize)
{
    for (int z = 0; z < zSize; z++)
    {
        for (int y = 0; y < ySize; y++)
        {
            for (int x = 0; x < xSize; x++)
            {
                array[z][y][x] = false;
            }
        }
    }
}

bool ***VoxelGrid::allocate3dBoolArray(int xSize, int ySize, int zSize)
{
    bool ***data = (bool ***)malloc(sizeof(bool **) * zSize);
    for (int z = 0; z < zSize; z++)
    {
        data[z] = (bool **)malloc(sizeof(bool *) * ySize);
        for (int y = 0; y < ySize; y++)
        {
            data[z][y] = (bool *)malloc(sizeof(bool) * xSize);
        }
    }
    return data;
}

void VoxelGrid::free3dBoolArray(bool ***array, int xSize, int ySize, int zSize)
{

    for (int z = 0; z < zSize; z++)
    {
        for (int y = 0; y < ySize; y++)
        {
            free(array[z][y]);
        }
        free(array[z]);
    }

    free(array);
}