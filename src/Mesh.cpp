//
// Created by matt on 24/04/19.
//

#include "../include/Mesh.h"
#include <igl/readOBJ.h>
#include "../include/Box.h"


using namespace Eigen;

void Mesh::loadFromFile(std::string filename) {
    Eigen::Matrix2Xf texCoords;
    Eigen::MatrixXi faceTex; //   FTC  #F list of face indices into vertex texture coordinates

    //Read file into our arrays
    igl::readOBJ(filename, this->vertices, texCoords, this->vertexNormals, this->faces, faceTex, this->faceVns);
}


bool Mesh::intersects(Box *box) {
    return false;
}

void Mesh::calculateTriangles() {
    //Turn loaded matrices into a vector of triangle objects
    this->triangles.empty();

    for (int f = 0; f < this->faces.rows(); f++) {
        const Vector3i face = this->faces.row(f);
        const Vector3i faceVns = this->faceVns.row(f);

        Matrix3f vs;
        Matrix3f vns;

        for (int v = 0; v < 3; v++) {
            vs.col(v) = (this->vertices.row(face(v)).transpose());
            vns.col(v) = (this->vertexNormals.row(faceVns(v)).transpose());
        }

        Triangle *t = new Triangle(vs);

        this->triangles.push_back(t);
    }

    this->trianglesCalculated = true;
}

Mesh::Mesh(std::string filename) {
    loadFromFile(filename);
    trianglesCalculated = false;
    boundingBoxCalculated = false;
    this->calculateTriangles();
    this->calculateBoundingBox();
}

Mesh::~Mesh() = default;

void Mesh::calculateBoundingBox() {
    this->boundingBox = Box();

    for (auto const &triangle : this->triangles) {
        for (int v = 0; v < 3; v++) {
            const Vec3 vertex = triangle->getVertex(v);

            this->boundingBox.expand(vertex);
        }
    }
    this->boundingBoxCalculated = true;
}
