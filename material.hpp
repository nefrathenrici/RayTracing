#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "util.hpp"
#include "hittable.hpp"

class material {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
    public:
        lambertian(const color& a);
        virtual ~lambertian() = default;

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const;
        color albedo;
};

class metal : public material {
    public:
        metal(const color& a, double f);
        virtual ~metal() = default;

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const;

        color albedo;
        double fuzz;
};

class dielectric : public material {
    public:
        dielectric(double index_of_refraction);
        ~dielectric() = default;

        bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const;

        double ir;  // Index of Refraction

    private:
        static double reflectance(double cosine, double ref_idx);
};

#endif  // MATERIAL_HPP_
