#include "geometry.hpp"

point_t operator+(const point_t &lhs, const point_t &rhs)
{
  point_t tmp(lhs);
  tmp += rhs;
  return tmp;
}

point_t operator-(const point_t &lhs, const point_t &rhs)
{
  point_t tmp(lhs);
  tmp -= rhs;
  return tmp;
}
