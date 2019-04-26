//
// Created by matt on 24/04/19.
//

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

    void loadFromFile(std::string filename);

    void calculateTriangles();

    void calculateBoundingBox();

    void buildKDTree();

    void deleteTriangles();

    void setSize(float size);

    void moveTo(Vec3 position);

    Mesh(std::string filename);

    virtual ~Mesh();

    bool intersects(Box *box) override;

  private:
    bool trianglesCalculated;
    bool boundingBoxCalculated;
    TriangleKDNode *kdTree;
    Vec3 translation = Vec3(0, 0, 0);
};

#endif  // VOXELISE_MESH_H
