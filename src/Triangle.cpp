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

Vec3 Triangle::getMidpoint() {
    //Uses caching only calculates once
    //Average the vertices of the triangle to get the midpoint

    if (!this->midPointCalculated) {
        Vec3 midPoint(0, 0, 0);

        for (int i = 0; i < 3; i++) {
            midPoint += this->getVertex(i);
        }

        midPoint /= 3;

        this->midPointCalculated = true;
        this->midPoint = midPoint;
        return midPoint;
    }

    return this->midPoint;
}

Box Triangle::getBoundingBox() {
    if (!this->boundingBoxCalculated) {
        Box b = Box();

        for (int i = 0; i < 3; i++) {
            b.expand(this->getVertex(i));
        }

        this->boundingBoxCalculated = true;
        this->boundingBox = b;
        return b;
    }

    return this->boundingBox;
}