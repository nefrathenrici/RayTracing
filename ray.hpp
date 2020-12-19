// Ray class (A+tb)
#ifndef RAY_HPP_
#define RAY_HPP_

#include "vec3.hpp"

class ray {
    public:
        // Constructors
        ray() {}
        ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction) {}

        point3 origin() const  { return orig; }
        vec3 direction() const { return dir; }

        point3 at(double t) const {
            // Compute A+tb
            return orig + t*dir;
        }
        point3 orig;
        vec3 dir;
};

#endif  // RAY_HPP_
