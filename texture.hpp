#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "color.hpp"

class texture {
    public:
        // Simple class, just contains fn returning color value at given coords
        virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture {
    // Texture with just one color - same at all points
    public:
        solid_color(color c);
        virtual ~solid_color() = default;
        
        solid_color(double r, double g, double b);

        color value(double u, double v, const point3& p) const;
        
    private:
        color color_val;
};

class checker : public texture {
    public:
        checker(shared_ptr<texture> _first, shared_ptr<texture> _second);
        checker(color _first, color _second);
        virtual ~checker() = default;

        color value(double u, double v, const point3& p) const;

        shared_ptr<texture> first;
        shared_ptr<texture> second;
};

#endif  // TEXTURE_HPP_