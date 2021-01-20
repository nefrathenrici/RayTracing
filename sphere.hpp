#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <memory>
#include "hittable.hpp"

class sphere : public hittable {
    public:
        sphere();
        sphere(point3 cen, double r, shared_ptr<material> m);
        virtual ~sphere() = default;

        bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

        bool bounding_box(double time0, double time1, aabb& output_box) const override;


    private:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
        
        static void get_sphere_coords(const point3& p, double& u, double& v);
};

#endif  // SPHERE_HPP_
