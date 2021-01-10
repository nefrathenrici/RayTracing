#ifndef HITTABLE_LIST_HPP_
#define HITTABLE_LIST_HPP_

#include <memory>
#include <vector>
#include "aabb.hpp"
#include "hittable.hpp"

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
    public:
        hittable_list();
        hittable_list(shared_ptr<hittable> object);
        virtual ~hittable_list() = default;

        void clear();

        void add(shared_ptr<hittable> object);

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

        virtual bool bounding_box(
            double time0, double time1, aabb& output_box) const override;

        std::vector<shared_ptr<hittable>> objects;
};

#endif  // HITTABLE_LIST_HPP_
