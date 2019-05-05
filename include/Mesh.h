#ifndef VOXELISE_MESH_H
#define VOXELISE_MESH_H

#include "Box.h"
#include "Intersectable.h"
#include "Triangle.h"
#include "TriangleKDNode.h"
#include "Vectors.h"

class Mesh : public Intersectable
{
public:
  Eigen::MatrixXf vertices;
  Eigen::MatrixXf vertexNormals;
  Eigen::MatrixXi faces;
  Eigen::MatrixXi faceVns;  //   FN  #F list of face indices into vertex normals
  Box boundingBox;

  std::vector<Triangle *> triangles;

  /**
   * Loads triangles from file into the matrices
   */
  void loadFromFile(std::string filename);

  /**
   * Fills the triangles vector with triangle objects built from the loaded data in the matrices
   */
  void calculateTriangles();

  /**
   * Calculate the smallest box that contains all triangles in the mesh
   */
  void calculateBoundingBox();

  /**
   * Puts all the triangles into a balanced KD-Tree for very fast intersection
   */
  void buildKDTree();

  /**
   * Deletes all generated triangles
   */
  void deleteTriangles();

  /**
   * Scales the mesh triangles
   */
  void setSize(float size);

  /**
   * Translates all triangles
   */
  void moveTo(Vec3 position);

  /**
   * Construct and read from file
   */
  Mesh(std::string filename);

  virtual ~Mesh();

  /**
   * Returns true if the mesh intersects with the supplied box
   */
  bool intersects(Box *box) override;

private:
  bool trianglesCalculated;
  bool boundingBoxCalculated;
  TriangleKDNode *kdTree;
  Vec3 translation = Vec3(0, 0, 0);
};

#endif  // VOXELISE_MESH_H
