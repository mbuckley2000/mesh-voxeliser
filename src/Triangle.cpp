//
// Created by matt on 24/04/19.
//

#include "../include/Triangle.h"

bool Triangle::intersects(Box *box) {
    for (int v = 0; v < 3; v++) {
        if (box->contains(this->getVertex(v))) {
            return true;
        }
    }

    return false;
}

Vec3 Triangle::getVertex(int vertex) {
    return this->vertices.col(vertex);
}

Triangle::Triangle(Vec3 v0, Vec3 v1, Vec3 v2) {
    this->vertices.col(0) = v0;
    this->vertices.col(1) = v1;
    this->vertices.col(2) = v2;
}

Triangle::Triangle(Mat3 vertices) {
    this->vertices = vertices;
}