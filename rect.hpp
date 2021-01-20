#ifndef RECT_HPP_
#define RECT_HPP_
#include "hittable.hpp"

class rect : public hittable {
    // Z-axis aligned, but will be able to be rotated
    // Rect coords: x=[x0,x1], y=[y0,y1],z=[k-0.0001,k+0.0001]
    public:
        rect( double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<material> mat);

        virtual ~rect() = default;

        bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

        bool bounding_box(double time0, double time1, aabb& output_box) const override;
    
        double x0, x1, y0, y1, k;
        shared_ptr<material> mat_ptr;
};

#endif  // RECT_HPP_
