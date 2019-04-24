//
// Created by matt on 24/04/19.
//

#ifndef VOXELISE_TRIANGLE_H
#define VOXELISE_TRIANGLE_H


#include "Intersectable.h"
#include "Vectors.h"
#include "Box.h"
#include <vector>

class Triangle :
        public Intersectable {
public:
    /**
     * Construct from three vertices
     */
    Triangle(Vec3 v0, Vec3 v1, Vec3 v2);

    /**
     * Construct from a 3x3 matrix containing the vertices and another containing the normals.
     */
    Triangle(Mat3 vertices);

    bool intersects(Box *box);

    /**
     * Returns the vertex (0, 1, 2) as a vector
     */
    Vec3 getVertex(int vertex);

private:
    Mat3 vertices;
};


#endif //VOXELISE_TRIANGLE_H
