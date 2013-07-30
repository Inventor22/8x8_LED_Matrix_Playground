
#include "Point.h"
#include "math.h"

Point::Point(int8_t _x, int8_t _y) :
    x(_x), y(_y) {
}

Point& Point::shift(int8_t _x, int8_t _y) {
    x += _x;
    y += _y;
}

Point& Point::shift(Point p) {
    x += p.x;
    y += p.y;
}

Point& Point::invert() {
    x ^= y;
    y ^= x;
    x ^= y;
    return *this;
}

Point& Point::negate() {
    return ((*this) *= -1);
}

float Point::norm() {
    return sqrt(x*x + y*y);
}

Point& Point::operator+=(const Point& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Point& Point::operator-=(const Point& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Point& Point::operator*=(const Point& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

Point& Point::operator*=(int factor) {
    x *= factor;
    y *= factor;
    return *this;
}

Point& Point::operator/=(const Point& rhs) {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
}

Point& Point::operator/=(int factor) {
    x /= factor;
    y /= factor;
    return *this;
}

inline Point& Point::operator%=(const Point& rhs) {
    x %= rhs.x;
    y %= rhs.y;
    return *this;
}

inline Point& Point::operator%=(int factor) {
    x %= factor;
    y %= factor;
    return *this;
}