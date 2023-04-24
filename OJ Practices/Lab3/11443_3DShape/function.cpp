#include <iostream>
#include "function.h"

using namespace std;

namespace oj {

Sphere::Sphere(double radius, double pi) : radius(radius), pi(pi) {
    if (radius < 0 || pi < 0) {
        setVolume(0);
    }
    else {
        setVolume((4.0 / 3.0) * pi * radius * radius * radius);
    }
}

Cone::Cone(double radius, double height, double pi) : radius(radius), height(height), pi(pi) {
    if (radius < 0 || height < 0 || pi < 0) {
        setVolume(0);
    }
    else {
        setVolume((1.0 / 3.0) * pi * radius * radius * height);
    }
}

Cuboid::Cuboid(double len, double w, double h) : length(len), width(w), height(h) {
    if (len < 0 || w < 0 || h < 0) {
        setVolume(0);
    }
    else {
        setVolume(len * w * h);
    }
}

Cube::Cube(double len) : Cuboid(len, len, len) { }

}
