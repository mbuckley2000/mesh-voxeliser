//
// Created by matt on 24/04/19.
//

#include "../include/Box.h"

Box::Box(Vec3 minimum, Vec3 maximum) {
    this->minimum = minimum;
    this->maximum = maximum;
}

Box::Box() {
    this->minimum << INFINITY, INFINITY, INFINITY;
    this->maximum << -INFINITY, -INFINITY, -INFINITY;
}

Box::~Box() = default;

bool Box::contains(Vec3 v) {
    for (int d = 0; d < 3; d++) {
        if (v(d) > this->maximum(d) || v(d) < this->minimum(d)) {
            return false;
        }
    }

    return true;
}

void Box::expand(Vec3 v) {
    for (int d = 0; d < 3; d++) {
        if (v[d] < this->minimum[d]) {
            this->minimum[d] = v[d];
        }
        if (v[d] > this->maximum[d]) {
            this->maximum[d] = v[d];
        }
    }
}

void Box::expand(Box b) {
    for (int d = 0; d < 3; d++) {
        if (b.minimum[d] < this->minimum[d]) {
            this->minimum[d] = b.minimum[d];
        }
        if (b.maximum[d] > this->maximum[d]) {
            this->maximum[d] = b.maximum[d];
        }
    }
}

int Box::largestDim() {
    float longest = 0;
    int dim = 0;

    Vec3 size = this->getSize();

    for (int d = 0; d < 3; d++) {
        const float length = size(d);
        if (length > longest) {
            longest = length;
            dim = d;
        }
    }

    return dim;
}

Vec3 Box::getSize() {
    return this->maximum - this->minimum;
}

bool Box::intersects(Box *box) {
    for (int dim = 0; dim < 3; dim++) {
        if (this->minimum(dim) > box->maximum(dim) || box->minimum(dim) > this->maximum(dim)) {
            return false;
        }
    }

    return true;
}