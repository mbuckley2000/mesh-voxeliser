#ifndef VOXELISE_TRIANGLE_H
#define VOXELISE_TRIANGLE_H

#include <vector>
#include "Box.h"
#include "Intersectable.h"
#include "Vectors.h"

class Triangle : public Intersectable
{
public:
  Vec3 normal;

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

  void calculateNormal();

  void calculateEdges();

  /**
   * Calculates the mid (average) point of the triangle
   * Will only be calculated once and then cached
   */
  Vec3 getMidpoint();

private:
  Mat3 vertices;
  Mat3 edges;
  Vec3 midPoint;
  bool midPointCalculated = false;
  Box boundingBox;
  bool boundingBoxCalculated = false;

  static void project(Eigen::MatrixXf points, Vec3 *axis, float *min, float *max);
};

#endif  // VOXELISE_TRIANGLE_H
