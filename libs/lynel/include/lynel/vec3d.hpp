// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_LYNEL_VEC3D_HPP
#define TYBL_LYNEL_VEC3D_HPP

namespace tybl::lynel {

struct vec3d {
  double x;
  double y;
  double z;
}; // struct vec3d

double dot(vec3d const& l, vec3d const& r);

double length(vec3d const& v);

} // namespace tybl::lynel

#endif // TYBL_LYNEL_VEC3D_HPP
