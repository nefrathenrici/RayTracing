// aabb.cpp

#include "aabb.hpp"

aabb::aabb() {}
aabb::aabb(const point3& a, const point3& b) {
    minimum = a;
    maximum = b;
}

point3 aabb::min() const {
    return minimum;
}

point3 aabb::max() const {
    return maximum;
}
bool aabb::hit(const ray& r, double t_min, double t_max) const {
    // Slightly unclear code below - compiles better!
    // Adapted from Andrew Kensler at Pixar
    for (int dim = 0; dim <3; ++dim) {
    // Loop through all 3 dimensions
        float invert = 1.0f / r.direction()[dim];  // Used to invert direction if needed
        double t0 = (min()[dim] - r.origin()[dim]) * invert;
        auto t1 = (max()[dim] - r.origin()[dim]) * invert;
        if (invert < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;

    }
    return true;
}

aabb surrounding_box(aabb box0, aabb box1) {
    point3 small(fmin(box0.min().x(), box1.min().x()),
                 fmin(box0.min().y(), box1.min().y()),
                 fmin(box0.min().z(), box1.min().z()));

    point3 big(fmax(box0.max().x(), box1.max().x()),
               fmax(box0.max().y(), box1.max().y()),
               fmax(box0.max().z(), box1.max().z()));

    return aabb(small,big);
}
