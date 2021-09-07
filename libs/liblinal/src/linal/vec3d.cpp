// License: The Unlicense (https://unlicense.org)
#include "linal/vec3d.hpp"

#include <math.h>

namespace tybl::linal {

double dot(vec3d const& l, vec3d const& r) {
  return (l.x*r.x) + (l.y*r.y) + (l.z*r.z);
}

double length(vec3d const& v) {
  return sqrt(dot(v,v));
}

} // namespace tybl::linal
