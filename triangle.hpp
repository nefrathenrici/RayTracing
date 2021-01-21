#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_
#include "hittable.hpp"

class triangle : public hittable {
    // Triangle defined by three points
    public:
        triangle(point3 _p0, point3 _p1, point3 _p2, shared_ptr<material> mat);

        virtual ~triangle() = default;

        bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

        bool bounding_box(double time0, double time1, aabb& output_box) const override;
    
        // Triangle defined by 3 points - added plane constant for faster hit computation
        point3 p0, p1, p2;
        vec3 p0p1, p0p2, n;
        double d;
        shared_ptr<material> mat_ptr;
};

#endif  // TRIANGLE_HPP_
