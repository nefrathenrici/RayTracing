// triangle.cpp
#include "triangle.hpp"
#include "util.hpp"

triangle::triangle(point3 _p0, point3 _p1, point3 _p2, shared_ptr<material> mat)
     : p0(_p0), p1(_p1), p2(_p2), mat_ptr(mat) {
    p0p1 = p1-p0;
    p0p2 = p2-p0;
    n = cross(p1-p0, p2-p0);
    d = dot(n, p0); 
}

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // Implementing Moller Trumbore algorithm for ray-triangle intersection
    vec3 p_vec = cross(r.direction(), p0p2);
    double det = dot(p0p1, p_vec); 

    if (det < 0.00001)  // triangle is parallel to or behind the ray
        return false;

    double inv_det = 1 / det;  

    vec3 t_vec = r.origin() - p0; 
    double u = dot(t_vec, p_vec) * inv_det;
    if (u < 0.0 || u > 1.0) 
        return false; 

    vec3 q_vec = cross(t_vec, p0p1);
    double v = dot(r.direction(), q_vec) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return false; 
    
    double t = dot(p0p2, q_vec) * inv_det;
    if (t < t_min || t > t_max) {
        return false;
    } else if (t > 0.00001) {
        rec.u = 0.5;
        rec.v = 0.5;
        rec.t = t;
        rec.set_face_normal(r, n);
        rec.mat_ptr = mat_ptr;
        rec.p = r.at(t);
        return true;
    }
    return false;
}

bool triangle::bounding_box(double time0, double time1, aabb& output_box) const {
    double min_x, max_x, min_y, max_y, min_z, max_z;
    double epsilon = 0.0000001;
    min_max(p0.x(), p1.x(), p2.x(),min_x, max_x);
    min_max(p0.y(), p1.y(), p2.y(),min_y ,max_y);
    min_max(p0.z(), p1.z(), p2.z(),min_z ,max_z);
    // Add padding if triangle is axis-aligned
    if (min_x == max_x)
        min_x -= epsilon;
        max_x += epsilon;
    if (min_y == max_y)
        min_y -= epsilon;
        max_y += epsilon;
    if (min_z == max_z)
        min_z -= epsilon;
        max_z += epsilon;
    output_box = aabb(point3(min_x, min_y, min_z), point3(max_x, max_y, max_z));
    return true;
}