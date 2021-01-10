// Ray class (A+tb)
#ifndef RAY_HPP_
#define RAY_HPP_

#include "vec3.hpp"

class ray {
    public:
        // Constructors
        ray();
        ray(const point3& origin, const vec3& direction);
        point3 origin() const;
        vec3 direction() const;

        point3 at(double t) const;
        
        point3 orig;
        vec3 dir;
};

#endif  // RAY_HPP_
