#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_

#include <cmath>

struct point_t
{
  float x, y;

  point_t(float _x, float _y):
    x(_x), y(_y) {;}

  point_t():x(0), y(0) {;}

  point_t(const point_t &p): x(p.x), y(p.y) {;}

  const point_t perp(void) const {point_t p(-y,x); return p;}
  float length2(void) const {return (x*x + y*y);}
  float length(void) const {return sqrt(length2());}

  point_t &operator+=(point_t const &_p)
  {
    this->x += _p.x; this->y += _p.y;
    return *this;
  }
  
  point_t &operator-=(point_t const &_p)
  {
    this->x -= _p.x; this->y -= _p.y;
    return *this;
  }
  
  point_t const &operator=(const point_t &_p)
  {    
    this->x = _p.x; this->y = _p.y;
    return *this;
  }
  
};

point_t operator+(const point_t &lhs, const point_t &rhs);
point_t operator-(const point_t &lhs, const point_t &rhs);

typedef point_t vec2d_t;

struct line_t
{
  point_t p1, p2;
 
  line_t(int _x1, int _y1, int _x2, int _y2):
    p1(point_t(_x1, _y1)), p2(point_t(_x2,_y2)) {;}

  line_t(point_t _p1, point_t _p2): p1(_p1), p2(_p2) {;}

  float length2(void) const {return ((p2.x-p1.x)*(p2.x-p1.x))+((p2.y-p1.y)*(p2.y-p1.y));}

  float length(void) const {return sqrt(length2()); }
}; 

#endif
