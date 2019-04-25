//
// Created by matt on 24/04/19.
//

#include "../include/Triangle.h"

void Triangle::project(Eigen::MatrixXf points, Vec3 axis, float *min, float *max) {
    *min = INFINITY;
    *max = -INFINITY;

    for (int i = 0; i < points.cols(); i++) {
        float val = axis.dot(points.col(i));
        if (val < *min) *min = val;
        if (val > *max) *max = val;
    }
}


bool Triangle::intersects(Box *box) {
//    for (int v = 0; v < 3; v++) {
//        if (box->contains(this->getVertex(v))) {
//            return true;
//        }
//    }
//    return false;

    float triMin, triMax;

    //Box normals
    for (int d = 0; d < 3; d++) {
        Vec3 boxNormal = Vec3(0, 0, 0);
        boxNormal(d) = 1;
        this->project(this->vertices, boxNormal, &triMin, &triMax);
        if (triMax < box->minimum(d) || triMin > box->maximum(d)) {
            return false;
        }
    }

    float boxMin, boxMax;
    //Triangle normals
    float triOffset = this->normal.dot(this->getVertex(0));
    this->project(box->getVertices(), this->normal, &boxMin, &boxMax);
    if (boxMax < triOffset || boxMin > triOffset) {
        return false;
    }

    // Test the nine edge cross-products
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            // The box normals are the same as it's edge tangents
            Vec3 boxNormal = Vec3(0, 0, 0);
            boxNormal(j) = 1;
            Vec3 axis = this->edges.col(i).cross(boxNormal);
            this->project(box->getVertices(), axis, &boxMin, &boxMax);
            this->project(this->vertices, axis, &triMin, &triMax);
            if (boxMax < triMin || boxMin > triMax)
                return false; // No intersection possible
        }

    // No separating axis found.
    return true;
}

void Triangle::calculateNormal() {
    this->normal = this->edges.col(0).cross(this->edges.col(1));
}

void Triangle::calculateEdges() {
    this->edges = Mat3();
    this->edges.col(0) = this->getVertex(1) - this->getVertex(0);
    this->edges.col(1) = this->getVertex(2) - this->getVertex(0);
    this->edges.col(2) = this->getVertex(1) - this->getVertex(2);
}



Vec3 Triangle::getVertex(int vertex) {
    return this->vertices.col(vertex);
}

Triangle::Triangle(Vec3 v0, Vec3 v1, Vec3 v2) {
    this->vertices.col(0) = v0;
    this->vertices.col(1) = v1;
    this->vertices.col(2) = v2;
    this->calculateEdges();
    this->calculateNormal();
}

Triangle::Triangle(Mat3 vertices) {
    this->vertices = vertices;
    this->calculateEdges();
    this->calculateNormal();
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