#include <iostream>
#include <cmath>
#include "function.h"

using namespace std;

namespace oj {

void Rectangle::draw() {
    for (int i = 0; i < 4; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }
    width = abs(points[0].x - points[1].x);
    if (width == 0)
        width = abs(points[0].x - points[2].x);
    height = abs(points[0].y - points[1].y);
    if (height == 0)
        height = abs(points[0].y - points[2].y);
    area = width * height;
}

void Circle::draw() {
    int x, y;
    cin >> x >> y >> radius;
    if (radius < 0)
        radius = 0;
    points.push_back(Point(x, y));
    area = PI * radius * radius;
}

}
