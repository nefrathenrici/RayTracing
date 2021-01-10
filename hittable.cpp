// hittable.cpp
#include "hittable.hpp"

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal) {
    // check if ray is inside sphere
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}