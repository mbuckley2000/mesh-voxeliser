//
// Created by matt on 24/04/19.
//

#include "../include/Box.h"

Box::Box(Vec3 minimum, Vec3 maximum) {
    this->minimum = minimum;
    this->maximum = maximum;
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