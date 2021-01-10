#ifndef BVH_HPP
#define BVH_HPP

#include <algorithm>
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "util.hpp"

// Class for Bounding-volume hierarchies (BVH).
// The BVH is a hittable class which contains its own AABB and pointers to children sub-hittables.

class bvh_node : public hittable {
    public:
        bvh_node();

        bvh_node(const hittable_list& list, double time0, double time1);

        bvh_node(const std::vector<shared_ptr<hittable>>& src_objects, 
             size_t start, size_t end, double time0, double time1);
             
        virtual ~bvh_node() = default;
    
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

        shared_ptr<hittable> left;
        shared_ptr<hittable> right;
        aabb box;

};

#endif  // BH_HPP_