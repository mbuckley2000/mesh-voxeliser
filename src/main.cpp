#include <iostream>
#include <gtest/gtest.h>
#include <sys/stat.h>
#include "../include/Mesh.h"
#include "../include/VoxelGrid.h"

bool fileExists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char *argv[]) {
    // Check the number of parameters
    if (argc < 5) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <INPUT_FILE> <OUTPUT_FILE> <RESOLUTION> <MUM_THREADS>" << std::endl;
        return 1;
    }

    //Validate arguments
    //Check input file is a real file
    if (!fileExists(argv[1])) {
        std::cerr << "Input file does not exist: " << argv[1] << std::endl;
        return 1;
    }

    //TODO Check the input file has a valid extension

    Mesh mesh = Mesh(argv[1]);
    VoxelGrid voxelGrid = VoxelGrid(&mesh, atof(argv[3]), atoi(argv[4]));
    voxelGrid.voxelise();
    voxelGrid.writeToFile(argv[2]);

    return 0;



//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
}