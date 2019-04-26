#ifndef VOXELISE_INTERSECTABLE_H
#define VOXELISE_INTERSECTABLE_H

#include "Vectors.h"

class Box;

class Intersectable
{
  public:
    Intersectable() = default;

    virtual ~Intersectable() = default;

    /**
     * Returns true if the given box intersects the object
     */
    virtual bool intersects(Box *box) = 0;
};

#endif  // VOXELISE_INTERSECTABLE_H
