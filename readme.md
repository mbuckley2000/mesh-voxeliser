# C++ Mesh Voxeliser

A command line tool for voxelising .obj mesh files.

Outputs RAW uint8 binary files.

### Libraries:
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)
* [LibIGL](https://github.com/libigl/libigl)
* [googletest](https://github.com/google/googletest)

### Usage
Usage: ```./voxelise <INPUT_FILE> <OUTPUT_FILE> <RESOLUTION> <NUM_THREADS>```

**INPUT_FILE:** must be .obj triangle mesh

**OUTPUT_FILE:** RAW uint8 binary file

**RESOLUTION:** 3D resolution of voxel grid (ie. 100 resolution makes a 100x100x100 voxelisation)

**NUM_THREADS:**  Number of threads to use for voxelisation (should equal CPU core count for optimal speed)

### To compile and run
**Ensure that you have Eigen, LibIGL, and googletest installed and configured in CMakeLists.txt**

In shell:
```shell
cmake .
make
./voxelise
```