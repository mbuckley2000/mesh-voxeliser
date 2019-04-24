//
// Created by matt on 24/04/19.
//

#ifndef VOXELISE_MESH_H
#define VOXELISE_MESH_H

#include "Intersectable.h"
#include "Vectors.h"
#include "Triangle.h"
#include "Box.h"

class Mesh :
        public Intersectable {
public:
    Eigen::MatrixXf vertices;
    Eigen::MatrixXf vertexNormals;
    Eigen::MatrixXi faces;
    Eigen::MatrixXi faceVns;//   FN  #F list of face indices into vertex normals
    Box boundingBox;

    std::vector<Triangle *> triangles;

    void loadFromFile(std::string filename);

    void calculateTriangles();

    void calculateBoundingBox();

    Mesh(std::string filename);

    virtual ~Mesh();


    virtual bool intersects(Box *box) override;

private:
    bool trianglesCalculated;
    bool boundingBoxCalculated;
};


#endif //VOXELISE_MESH_H
