#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "texture.hpp"
#include "hittable.hpp"

class material {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
    public:
        lambertian(const color& a);
        
        lambertian(shared_ptr<texture> a);

        virtual ~lambertian() = default;

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const;

        shared_ptr<texture> albedo;
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
        virtual ~dielectric() = default;

        bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const;

        double ir;  // Index of Refraction

    private:
        static double reflectance(double cosine, double ref_idx);
};

// Lights - in progress

// class diffuse_light : public material {
//     public:

// }

#endif  // MATERIAL_HPP_
