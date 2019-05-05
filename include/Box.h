#ifndef VOXELISE_BOX_H
#define VOXELISE_BOX_H

#include "Intersectable.h"
#include "Vectors.h"

class Box : Intersectable
{
public:
  Vec3 minimum, maximum;

  Box();
  Box(Vec3 minimum, Vec3 maximum);

  virtual ~Box();

  /**
   * Expands the box to include the given point
   */
  void expand(Vec3 v);

  /**
   * Expands the box to include the given box
   */
  void expand(Box b);

  /**
   * Returns the largest dimension (0, 1, 2) of the box
   */
  int largestDim();

  Vec3 getSize();

  Eigen::MatrixXf getVertices();

  bool intersects(Box *box) override;

private:
  bool verticesCalculated = false;
  Eigen::MatrixXf vertices;
};

#endif  // VOXELISE_BOX_H