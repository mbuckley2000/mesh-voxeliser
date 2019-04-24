//
// Created by matt on 24/04/19.
//

#ifndef VOXELISE_BOX_H
#define VOXELISE_BOX_H

#include "Vectors.h"

class Box {
public:
    Vec3 minimum, maximum;

    Box();
    Box(Vec3 minimum, Vec3 maximum);

    virtual ~Box();

    bool contains(Vec3 v);

    /**
	 * Expands the box to include the given point
	 */
    void expand(Vec3 v);
};

#endif //VOXELISE_BOX_H