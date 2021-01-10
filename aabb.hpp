#ifndef AABB_HPP_
#define AABB_HPP_

#include "util.hpp"
#include "ray.hpp"

// Contains code for axis-aligned bounding boxes (AABB)
// Used for hierarchical hit detection

class aabb {
    public:
        aabb();
        aabb(const point3& a, const point3& b);

        point3 min() const;

        point3 max() const;

        bool hit(const ray& r, double t_min, double t_max) const;

        point3 minimum;
        point3 maximum;
};

aabb surrounding_box(aabb box0, aabb box1);

#endif  // AABB.HPP_
