// rect.cpp
#include "rect.hpp"

rect::rect( double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<material> mat)
    : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat_ptr(mat) {}

bool rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    double t = (k-r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        // Ray doesn't fall within t_min/max range 
        return false;

    double x = r.origin().x() + t*r.direction().x();
    double y = r.origin().y() + t*r.direction().y();

    if (x < x0 || x > x1 || y < y0 || y > y1)
        // Ray doesn't intersect coords
        return false;
    
    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0);
    rec.t = t;
    auto outward_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.p = r.at(t);
    return true;
}

bool rect::bounding_box(double time0, double time1, aabb& output_box) const {
    output_box = aabb(point3(x0,y0, k-0.0001), point3(x1, y1, k+0.0001));
    return true;
}
