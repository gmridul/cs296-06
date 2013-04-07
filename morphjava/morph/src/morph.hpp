#ifndef _MORPH_HPP_
#define _MORPH_HPP_

#include "geometry.hpp"
#include <ImageMagick/Magick++.h>

float compute_u(const line_t &l, const point_t &p);
float compute_v(const line_t &l, const point_t &p);
point_t calc_dst_pixel(float u, float v, const line_t &l, const point_t &p);
void morph_frame(int framenum, int totalframes);

#endif
