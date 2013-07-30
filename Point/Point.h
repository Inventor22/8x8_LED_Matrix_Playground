// Point.h

#ifndef POINT_H
#define POINT_H

#include "stdint.h"

class Point {
 public:
     int8_t x, y;

public:
     Point(int8_t _x=0, int8_t _y=0);
     Point& shift(int8_t _x, int8_t _y);
     Point& shift(Point p);
     Point& invert();
     Point& negate();
     float norm();

     inline Point& operator+=(const Point& rhs);
     inline Point& operator-=(const Point& rhs);
     inline Point& operator*=(const Point& rhs);
     inline Point& operator*=(int factor);
     inline Point& operator/=(const Point& rhs);
     inline Point& operator/=(int factor);
     inline Point& operator%=(const Point& rhs);
     inline Point& operator%=(int factor);
};

inline bool  operator==(Point a, Point b)   { return (a.x==b.x && a.y==b.y);  }
inline bool  operator!=(Point a, Point b)   { return !(a==b);                 }
inline Point operator+(Point a, Point b)    { return Point(a.x+b.x, a.y+b.y); }
inline Point operator-(Point a, Point b)    { return Point(a.x-b.x, a.y-b.y); }
inline Point operator*(Point a, Point b)    { return Point(a.x*b.x, a.y*b.y); }
inline Point operator*(Point a, int c  )    { return Point(a.x*c,   a.y*c  ); }
inline Point operator/(Point a, Point b)    { return Point(a.x/b.x, a.y/b.y); }
inline Point operator/(Point a, int c  )    { return Point(a.x/c,   a.y/c  ); }
inline Point operator%(Point a, Point b)    { return Point(a.x%b.x, a.y%b.y); }
inline Point operator%(Point a, int c  )    { return Point(a.x%c,   a.y%c  ); }

#endif

