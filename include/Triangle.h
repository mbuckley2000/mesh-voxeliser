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

    bool intersects(Box *box) override;

    /**
     * Returns the vertex (0, 1, 2) as a vector
     */
    Vec3 getVertex(int vertex);

    /**
	 * Calculated a bounding box containing all vertices of the triangle
	 * WIll only be calculated once and then cached
	 */
    Box getBoundingBox();

    /**
	 * Calculates the mid (average) point of the triangle
	 * Will only be calculated once and then cached
	 */
    Vec3 getMidpoint();

private:
    Mat3 vertices;
    Vec3 midPoint;
    bool midPointCalculated = false;
    Box boundingBox;
    bool boundingBoxCalculated = false;
};


#endif //VOXELISE_TRIANGLE_H
