//
// Created by matt on 24/04/19.
//

#ifndef VOXELISE_TRIANGLEKDNODE_H
#define VOXELISE_TRIANGLEKDNODE_H

#include "Vectors.h"
#include "Box.h"
#include "Triangle.h"
#include "Intersectable.h"

class TriangleKDNode {
public:
    Box boundingBox;
    TriangleKDNode *left;
    TriangleKDNode *right;
    std::vector<Triangle *> triangles;

    /**
     * Construct and empty leaf node of the tree
     */
    TriangleKDNode();

    /**
     * Construct and balance a tree of the given triangles
     */
    TriangleKDNode(std::vector<Triangle *> triangles);

    /**
     * Returns true if the given ray intersects with a triangle in the tree
     * Object*& o will be set to contain a pointer to the intersected triangle
     * float& t will be set to contain the distance along the ray of the intersection point
     */
    bool intersects(Box *box);

private:
    /**
     * Builds a balanced KD tree from the triangles
     */
    void balance();

    /**
     * Expands the bounding box to contain all of the triangles
     */
    void expandBoundingBox();
};


#endif //VOXELISE_TRIANGLEKDNODE_H
