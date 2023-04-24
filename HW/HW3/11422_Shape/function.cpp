#include <iostream>
#include <string>
#include <cmath>

#include "function.h"

using namespace std;
using namespace oj;

Triangle::Triangle(double edge1, double edge2, double edge3) : edge1(edge1),edge2(edge2), edge3(edge3) {
    if (edge1 < 0 || edge2 < 0 || edge3 < 0) {
        setArea(0);
        setPerimeter(0);
    }
    else if (edge1 + edge2 <= edge3 || edge1 + edge3 <= edge2 || edge3 + edge2 <= edge1) {
        setArea(0);
        setPerimeter(0);
    }
    else {
        double s = (edge1 + edge2 + edge3) / 2;
        setArea(sqrt(s * (s - edge1) * (s - edge2) * (s - edge3)));
        setPerimeter(edge1 + edge2 + edge3);
    }
}

Rectangle::Rectangle(double width, double height) : width(width), height(height) {
    if (width < 0 || height < 0) {
        setArea(0);
        setPerimeter(0);
    }
    else {
        setArea(width * height);
        setPerimeter(2 * width + 2 * height);
    }
}

Circle::Circle(double radius, double pi) : radius(radius), pi(pi) {
    if (radius < 0 || pi < 0) {
        setArea(0);
        setPerimeter(0);
    }
    else {
        setArea(pi * radius * radius);
        setPerimeter(2 * pi * radius);
    }
}
