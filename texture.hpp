#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "color.hpp"

class texture {
    public:
        // Simple class, just contains fn returning color value at given coords
        virtual color value(double u, double v, const point3& p) = 0;
};

class solid_color : public texture {
    // Texture with just one color - same at all points
    public:
        solid_color(color c);
        virtual ~solid_color() = default;
        
        solid_color(double r, double g, double b);

        color value(double u, double v, const point3& p);
        
    private:
        color color_val;
};

#endif  // TEXTURE_HPP_